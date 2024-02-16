import cv2
from cvzone.HandTrackingModule import HandDetector
import serial
import time

arduino = serial.Serial('/dev/ttyACM0', 115200)
time.sleep(2)



    


cap = cv2.VideoCapture(0)
detector = HandDetector()



#con il pollice sinitro attivo sensore
#con il pollice destro disattivo sensore
#intensita 100,150,200,220,255
#con due mani spengo il motre;situazione emergeza


sensor = "0"
intervallo_secondi = 1  # Intervallo desiderato in secondi
ultima_esecuzione = time.time()  # Inizializza il tempo dell'ultima esecuzione

while True:
    
    tempo_corrente = time.time()
    success, img = cap.read()
    img = cv2.resize(img, (1280, 720))
    hands, img = detector.findHands(img)
    if hands:
        if len(hands) == 2:
            comando = "000"
        else:    
            hand = hands[0]
            hand_type = hand["type"]
            # Riconoscimento delle dita sollevate
            fingers_up = detector.fingersUp(hand)   
            # Conta le dita sollevate
            fingers_count = fingers_up.count(True)
            #capire se ho il polllice sollevato
            if fingers_up[0] == 1 and fingers_up[1] == 0 and fingers_up[2] == 0 and fingers_up[3] == 0 and fingers_up[4] == 0:
                if hand_type == "Left":
                    sensor = "1"
                else:
                    sensor = "0"    
            comando = "0"
            # Tipo di mano (sinistra o destra)
            
            if hand_type == "Left": #avanti con velocità fingers_count
                comando = "1" + str(fingers_count) + sensor
            else:
                comando = "2" + str(fingers_count) + sensor
    
        if tempo_corrente - ultima_esecuzione >= intervallo_secondi:
            print(comando)
            #comando += "\n"
            arduino.write(comando.encode())
            ultima_esecuzione = tempo_corrente  # Aggiorna il tempo dell'ultima esecuzione
           
    else:
        comando = "000"
        if tempo_corrente - ultima_esecuzione >= intervallo_secondi:
            print(comando)
            #comando += "\n"
            arduino.write(comando.encode())
            ultima_esecuzione = tempo_corrente  # Aggiorna il tempo dell'ultima esecuzione

    cv2.imshow("run", img)

    # y aumenta verso il basso
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break



