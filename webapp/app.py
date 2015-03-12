#!/usr/bin/python
from flask import Flask, render_template, send_from_directory, request, jsonify
import os

app = Flask(__name__)

''' Channel Config 1-5. Chan 0 fuer alle 5 Channels gleichzeitig
	Mode 1 HOCH - Mode 2 Runter - Mode 3 Stop '''
config = {'chan0mode1':  '', 'chan0mode2': '', 'chan0mode3': '', 'chan1mode1': '', 'chan1mode2': '', 'chan1mode3': '', 'chan2mode1': '', 'chan2mode2': '', 'chan2mode3': '', 'chan3mode1': '0FF10100F0001F010F0F', 'chan3mode2': '0FF10100F0001F010101', 'chan3mode3': '0FF10100F0001F01FFFF', 'chan4mode1': '', 'chan4mode2': '', 'chan4mode3': '', 'chan5mode1': '', 'chan5mode2': '', 'chan5mode3': ''}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/api', methods=['POST'])
def rollo_switch():
        json = request.json
        #print(json)
        #print(request.json['chan'])
        #1 hoch - 2 runter - 3 stop
        #print(request.json['mode'])
	if int(request.json['chan']) <= 5 :
		todo = "chan" + str(request.json['chan']) + "mode" + str(request.json['mode'])
        	#print(todo)
		if config[todo] != '':
			cmdsend = "sudo bin/sendv2 " + str(config[todo]) 
			#print(cmdsend)
			os.system(cmdsend);
			return jsonify({'ok': 'Done'})
		else:
			return jsonify({'error': 'Geraetecode nicht gesetzt'})
	else:
		return jsonify({'error': 'Wrong Channel'})

if __name__ == '__main__':
    	#app.debug = True
	app.run(host='0.0.0.0')
