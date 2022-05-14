import java.io.*;
import java.net.*;

class UDPClient
{
   public static void main(String args[]) throws Exception
   {
      BufferedReader inFromUser =
         new BufferedReader(new InputStreamReader(System.in));
      DatagramSocket clientSocket = new DatagramSocket();
      InetAddress IPAddress = InetAddress.getByName("fd00::201:1:1:1");
      byte[] sendData = new byte[1024];
      byte[] receiveData = new byte[1024];
      String sentence = inFromUser.readLine();
      sendData = sentence.getBytes();

      System.out.println("SENDING:" + sentence);
      DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 60001);
      clientSocket.send(sendPacket);
      clientSocket.close();
   }
}
