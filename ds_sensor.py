import onewire
import ds18x20
import machine
import time
import network
from simple import MQTTClient


s = 0
roms = []
c = 0
temp = 0
topic = ''
client_id = ''

def do_connect():
    SSID = 'your SSID'
    PASSWORD = 'your PWD'
    sta_if = network.WLAN(network.STA_IF)
    ap_if = network.WLAN(network.AP_IF)
    if ap_if.active():
        ap_if.active(False)
    if sta_if.active(False):
        sta_if.active()
    if not sta_if.isconnected():
        print('connecting to network...')
        sta_if.active(True)
        sta_if.connect(SSID, PASSWORD)
        while not sta_if.isconnected():
            pass
    print('Network configuration:', sta_if.ifconfig())
    
    
def switch_off_wifi():
    print('Switching off WLAN')
    sta_if = network.WLAN(network.STA_IF)
    sta_if.disconnect()  
    sta_if.active(False)

    
    
def set_sensor():
    dat = machine.Pin(2)
    ow = onewire.OneWire(dat)
    global ds
    ds = ds18x20.DS18X20(ow)
    global roms
    roms = ds.scan()
    print('found devices:', roms)


def read_sensor():    
    print('temperatures:', end=' ')
    ds.convert_temp()
    time.sleep_ms(750)
    for rom in roms:
        global temp
        temp = ds.read_temp(rom)
        if isinstance (temp, float):
            temp = round(temp, 2) #round the reading to 2 digits from the decimal point
            print(temp, end=' ')
        else:
            print('error in reading sensor')
        print()
            
            
def connect_mqtt():
    server = "server IP"
    global client_id
    client_id = "client" #insert your client ID
    username='user' #insert your MQTT username
    password='pwd' #insert your MQTT password
    global topic
    topic = ('sensor/temperature')
    global c
    c = MQTTClient(client_id,server,0,username,password)
    c.connect()
    time.sleep(3)

def publish_temp():
    print('publishing: ',temp)
    c.publish(topic, str(temp)) 
    time.sleep(3) #Wait to be sure the message has time to be sent

            
        
        
set_sensor()
while True:
    do_connect()
    connect_mqtt()
    read_sensor()
    publish_temp()
    switch_off_wifi()
    time.sleep(300) #sleep 5 minutes
   
        

