
 
char FileBuffer[16]; //set up space to read in files
// define values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
// define variable used for temp
char scale[4];
char raw[4];
char offset[4];
int raw_i;
int scale_i;
int offset_i;
int temp;


String operator + (String a, String b) {
  String result;
  result = a;
  result += b;
  return result;
}
 
 
void setup() {
  
  Serial.begin(57600);
  // put your setup code here, to run once:
  String year, month, day, hour, minute;
  String dateTime, timeCommand;
  char buffer[100];
 
  // Set time manually
  year   = "2014";
  month  = "3";    // March
  day    = "5";
  hour   = "15";  // 15 is 3 PM UTC, or 8 am MST
  minute = "20";
 
  delay (3000);  // delay three seconds to allow user to open the monitor
  dateTime = year + "." + month + "." + day + "-" + hour + ":" + minute;
 
 
  // Set time manually and print it out
  timeCommand = "(date -s" + dateTime + "; TZ=MST+7 date) >/dev/ttyGS0";
  timeCommand.toCharArray(buffer, 99);
  system (buffer);
  
  Serial.println (dateTime);
 
 
//Set time from the internet and print it out 
  system ("(TM=$(curl -s  http://www.timeapi.org/utc/now?format=%25Y.%25m.%25d-%25H:%25M); \
      date -s $TM; \
      TZ=MST+7 date ) >/dev/ttyGS0");
 
 
 
}
 
 
void loop() {
  // put your main code here, to run repeatedly:
  
  
 
  //Get Date
     system("date '+DATE: %m/%d/%y' > /home/root/date.txt");
     FILE *fp;
     fp=fopen("/home/root/date.txt","r");
     fgets(FileBuffer, 16, fp);
     fclose(fp);
 
     Serial.print(FileBuffer);
 
  //Get Time
   system("date '+%H:%M:%S' > /home/root/date.txt");
     fp=fopen("/home/root/date.txt","r");
     fgets(FileBuffer, 16, fp);
     fclose(fp);
     
     Serial.print(FileBuffer);
 
 
     delay(1000);
     
     
 // FILE *fp;
     system("date '+%S' > /home/root/date.txt");
     fp=fopen("/home/root/date.txt","r");
     fgets(FileBuffer, 16, fp);
     fclose(fp);
     int number = atoi( FileBuffer );
     Serial.println(number);
     
     number = number + 12;
     Serial.println(number);
 
}

void get_hour() {
  
  int hour;
  FILE *fp;
     system("date '+%H' > /home/root/date.txt");
     fp=fopen("/home/root/date.txt","r");
     fgets(FileBuffer, 16, fp);
     fclose(fp);
     int number = atoi( FileBuffer );
     Serial.print(number);
  
}
