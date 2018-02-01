/*
 * UIPEthernet UdpClient example.
 *
 * UIPEthernet is a TCP/IP stack that can be used with a enc28j60 based
 * Ethernet-shield.
 *
 * UIPEthernet uses the fine uIP stack by Adam Dunkels <adam@sics.se>
 *
 *      -----------------
 *
 * This UdpClient example tries to send a packet via udp to 192.168.0.1
 * on port 5000 every 5 seconds. After successfully sending the packet it
 * waits for up to 5 seconds for a response on the local port that has been
 * implicitly opened when sending the packet.
 *
 * Copyright (C) 2013 by Norbert Truchsess (norbert.truchsess@t-online.de)
 */

#include <SPI.h>
#include <UIPEthernet.h>

EthernetUDP udp;
unsigned long next;

byte enviabuffer[2];
int leiturasensor;

void setup() {

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(192,168,0,6));

  next = millis()+100;
}

void loop() {

  int success;
  int len = 0;

  if (((signed long)(millis()-next))>0)
    {
      do
        { 
          success = udp.beginPacket(IPAddress(192,168,0,1),5000);
          Serial.print("beginPacket: ");
          Serial.println(success ? "success" : "failed");
          //beginPacket fails if remote ethaddr is unknown. In this case an
          //arp-request is send out first and beginPacket succeeds as soon
          //the arp-response is received.
        }
      while (!success && ((signed long)(millis()-next))<0);
      if (!success )
        goto stop;

       leiturasensor = analogRead(A4);

       Serial.print("Número Lido:""\n");

       Serial.print(leiturasensor);

       Serial.print("\n");     
       
       enviabuffer[0] = leiturasensor/256;
       enviabuffer[1] = leiturasensor%256;
     
      success = udp.write(enviabuffer,sizeof(enviabuffer));

      Serial.print("bytes written: ");
      Serial.println(success);

      success = udp.endPacket();

      Serial.print("endPacket: ");
      Serial.println(success ? "success" : "failed");

      stop:
      udp.stop();
      next = millis()+100; 
    }
}

 


