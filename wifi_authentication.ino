#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "NTU";
const char* host = "210.29.79.141";
String userid = "";//学号
String password = "";//密码
String device = "1";//1是移动端，0是PC端

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid,"");
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(200);
  }
  Serial.println("NTU connected");
  Serial.println(WiFi.localIP());
  delay(1000);
  WiFiClient client;
  client.connect( host, 801 );
  String request = (String) ("GET ") + "/eportal/?c=Portal&a=login&callback=dr1003&login_method=1&user_account=,1," + userid + "&user_password=" + password + "&wlan_user_ip=" + WiFi.localIP().toString() + " HTTP/1.1\r\n" +
       "Host: " + host + ":801" + "\n" +
       "Connection: Keep Alive\r\n\r\n";
  client.print( request );
  String response = client.readString();
  int head = response.indexOf("Set-Cookie: PHPSESSID=")+22;
  String cookie = response.substring(head,head+26);
  Serial.println("successed in getting session"); Serial.println(cookie);
  delay(1000);
  client.connect( host, 801 );
  request = (String) ("GET ") + "/eportal/?c=Portal&a=login&callback=dr1003&login_method=1&user_account=,1," + userid + "&user_password=" + password + "&wlan_user_ip=" + WiFi.localIP().toString() +"&wlan_user_ipv6=&wlan_user_mac=000000000000&wlan_ac_ip=&wlan_ac_name=ME60&jsVersion=3.3.2&v=8322 HTTP/1.1\n" + +
       "Accept: */*" +
       "Accept-Encoding: gzip, deflate\n" +
       "Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6\n" +
       "Cache-Control: max-age=0\n" +
       "Connection: Keep Alive\n" +
       "Cookie: PHPSESSID=" + cookie + "\n" +
       "Host: " + host + ":801\n" +
       "Referer: http://210.29.79.141/\n";
  client.print( request );
  HTTPClient webtest;
  webtest.begin("http://baidu.com");
  int code = webtest.GET();
  Serial.println(code);
  if (code == 200)
  {Serial.println("Sucessful Internet access");}
  webtest.end();
  delay(1000);
  client.stop();
}

void loop(){
  
}
