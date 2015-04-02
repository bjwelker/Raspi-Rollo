int logfile[40];
int i = 0;
float lastTime = 0;
boolean capturing = false;
boolean checking = false;
boolean dataIncoming = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Bereit...");
  pinMode(2, INPUT);
  attachInterrupt(0, handleInterrupt, CHANGE);
}

void loop() {
}

void handleInterrupt() {

  if (!capturing) {  //wenn keine Aufnahme läuft
    if (!checking) {  //wenn nicht gerade auf "Start-Signal" geprüft wird
      if (digitalRead(2) == HIGH) {  //wenn Wechsel von LOW nach (jetzt) HIGH
        lastTime = micros();
        checking = true;
      }
    }

    else {    //wenn gerade auf Start-Signal geprüft wird
      if ((micros() - lastTime > 4000) && (digitalRead(2) == LOW)) {    //wenn HIGH-Phase länger als 4ms war und wir jetzt LOW sind
        //das war das Start-Signal
        checking = false;
        capturing = true;
        lastTime = micros();
      }

      else {
        //das war nicht das Start-Signal
        checking = false;
      }
    }
  }

  else {  //es läuft eine Aufnahme
    if (!dataIncoming) {  //bisher noch keine Nutzdaten empfangen
      if ((micros() - lastTime > 1000) && digitalRead(2) == HIGH) {  //das war die lange LOW-Phase vor Beginn der Übertragung
        dataIncoming = true; //ab jetzt kommen Daten  
        lastTime = micros();
      }
    }

    else {  //jetzt wird es interessant, jetzt kommen die Daten
      //wenn steigene Flanke (also jetzt HIGH)
      if (digitalRead(2) == HIGH) {
        //Beginn der HIGH-Phase merken
        lastTime = micros();
      }  

      //wenn fallende Flanke (also jetzt LOW) 
      else if (digitalRead(2) == LOW) {
        //=> prüfe wie lange HIGH war
        if (micros() - lastTime > 500) {
          //long
          logfile[i] = 1;
        }

        else {
          //short
          logfile[i] = 0;
        }

        if (i < 39) {
          //solange noch nicht alle Bits empfangen wurden
          i++;
        }

        else {
          //wir sind fertig
          noInterrupts();  //Interrupts aus damit Ausgabe nicht gestört wird
          Serial.println("Empfangene Daten:");
          //Ausgabe als "quad-bit"
          for (i = 0; i <= 38; i = i + 2) {
            if ((logfile[i] == 0) && (logfile[i+1] == 0))
              Serial.print("0");

            else if ((logfile[i] == 0) && (logfile[i+1] == 1))
              Serial.print("F");

            else if ((logfile[i] == 1) && (logfile[i+1] == 0))
              Serial.print("Q");

            else if ((logfile[i] == 1) && (logfile[i+1] == 1))
              Serial.print("1");
          }
          Serial.println();
          i = 0;
          dataIncoming = false;
          capturing = false;
          interrupts();  //Interrupts wieder an
          return;  //und alles auf Anfang
        }
      }

    }
  }
}

