#include<stdio.h>
#include<stdlib.h>
#include<utmpx.h>
#include<time.h>
#include<string.h>

#define REPORT_FILE "user_report.txt"
#define ALLOWED_FILE "allowed_users.txt"

char allowed_users[50][50];
int allowed_count=0;

void load_allowed_users() {
FILE *fp = fopen(ALLOWED_FILE, "r");
if(fp == NULL) {
printf("Could not open allowed_users.txt! All users will marked ALERT.\n");
return;
}

while(fgets(allowed_users[allowed_count],50,fp)){
allowed_users[allowed_count][strcspn(allowed_users[allowed_count], "\n")]=0;
allowed_count++;
}
fclose(fp);
}

//Check if the user is in allowed list
int is_allowed(char *user){
for (int i =0;i<allowed_count;i++){
if(strcmp(user,allowed_users[i]) == 0)
return 1;
}
return 0;
}

int main(){
struct utmpx *user_record;
FILE *report;
char timebuf[50];
load_allowed_users();

report = fopen(REPORT_FILE, "w");
if(report == NULL){
printf("Could not open report file!\n");
return 1;
}

fprintf(report, " =====================================\n");
fprintf(report, " USER ACTIVITY REPORT (%s)\n",__DATE__);
fprintf(report, " =====================================\n");
fprintf(report, " %-15s %-15s %-25s %-10s\n","Username","Terminal","Login Time","Status");
fprintf(report, " ---------------------------------------\n");

setutxent();

while((user_record =getutxent())){
if(user_record->ut_type==USER_PROCESS){
time_t login_time =user_record->ut_tv.tv_sec;
struct tm*lt = localtime(&login_time);
strftime(timebuf,sizeof(timebuf), "%Y=%m=%d %H:%M:%S", lt);

if(is_allowed(user_record->ut_user)){
fprintf(report, "%-15s %-15s %-25s %-10s\n",
user_record->ut_user,user_record->ut_line,timebuf,"Normal");
}
else{
fprintf(report, "%-15s %-15s %-25s %-10s\n",
user_record->ut_user,user_record->ut_line,timebuf,"Alert");
printf("ALERT: Unauthorized user '%s' logged in at %s\n",
user_record->ut_user,timebuf);
}
}
}

endutxent();
fclose(report);

printf("\n Report generated successfully:%s\n", REPORT_FILE);
return 0;
}



