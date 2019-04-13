#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User{
	char name[50];
	char phoneNo[10];
};
typedef struct User User;

time_t dataEntry(User* user, FILE *log);
void writeToFile(User *user);
char* getMonthName(int month);

int main(){
	
	int ch;
	char choice;
	User user;
	FILE *logfile;
	system("COLOR F0");
	time_t checkinTime,checkoutTime;
	struct tm *timeInfo;
	float perSecondCost = 2;
	
	
	do{
		system("cls");
		printf("\t\t\t\t\t\t\t...................\n");
        printf("\t\t\t\t\t\t\t|MATRIX CYBER CAFE|\n");
        printf("\t\t\t\t\t\t\t...................\n");
        printf("Press <1> Checkin for customer\n");
        printf("Press <2> Checkout for customer\n");
        printf("Press <3> To Exit\t\t\tCHARGES:: Rs 2/Sec\n");

    
        printf("\nEnter choice:: ");
		scanf("%d",&ch);
	
		switch(ch){
			case 1:
				checkinTime = dataEntry(&user,logfile);
				break;
			case 2:
				time(&checkoutTime);
				timeInfo = localtime(&checkoutTime);
				
				printf("\n\nUSER INFO: \nCustomer Name: %s\nMobile No: %s",user.name,user.phoneNo);
				printf("\nCheckout Time: %d:%d\nUsage: %d seconds\nTotal Amount: %.2f\n",timeInfo->tm_hour,timeInfo->tm_min,checkoutTime - checkinTime,(checkoutTime - checkinTime)*perSecondCost);
				logfile = fopen("LOG.txt","a+");
				fprintf(logfile,"Date: %d/%s/%d Checkout Time: %d:%d:%d\tTotal Amount:%0.2f\n",timeInfo->tm_mday,getMonthName(timeInfo->tm_mon),timeInfo->tm_year - 100 + 2000,timeInfo->tm_hour,timeInfo->tm_min,timeInfo->tm_sec,(checkoutTime - checkinTime)*perSecondCost);
				fclose(logfile);
				break;
			case 3:
   			exit(0);
    		break;
    		default:
    		printf("error");
		}
		
		printf("\nDo you wanna continue this app? (y/n): ");
		fflush(stdin);
		choice = getchar();
	}while(choice == 'y' || choice == 'Y');
}

time_t dataEntry(User *user, FILE *log){
	printf("\nEnter user name: ");
	fflush(stdin);
	gets(user->name);
	printf("\nEnter user mobile no: ");
	fflush(stdin);
	gets(user->phoneNo);
	
	writeToFile(user);
	
	log = fopen("LOG.txt","a+");
	
	time_t rawTime;
	struct tm *timeInfo;
	
	time(&rawTime);
	timeInfo = localtime(&rawTime);
	
	fprintf(log,"Mobile No.: %s\tDate: %d/%s/%d Checkin Time: %d:%d:%d\t",user->phoneNo,timeInfo->tm_mday,getMonthName(timeInfo->tm_mon),timeInfo->tm_year - 100 + 2000,timeInfo->tm_hour,timeInfo->tm_min,timeInfo->tm_sec);
	fclose(log);
	return rawTime;
}
void writeToFile(User *user){
	
	FILE *fp;
	char data[100];
	int hasPhoneNo = 0;
	fp = fopen("Records.txt","a+");
	//code to check if phone no exists in file or not
	
	while(!feof(fp)){
		fscanf(fp,"%s",data);
		
		hasPhoneNo = strcmp(user->phoneNo,data);

		if (!hasPhoneNo){
			
			fclose(fp);
			break;
			
		}
	}
	if (hasPhoneNo != 0){
		fprintf(fp,"\nMobile No.: %s\nName: %s \n\n",user->phoneNo,user->name);
		fclose(fp);
	}
}
char* getMonthName(int month){
	switch(month){
		case 0:
			return "January";
		case 1:
			return "February";
		case 2:
			return "March";
		case 3:
			return "April";
		case 4:
			return "May";
		case 5:
			return "June";
		case 6:
			return "July";
		case 7:
			return "August";
		case 8:
			return "September";
		case 9:
			return "October";
		case 10:
			return "November";
		case 11:	
			return "December";
	}
}
