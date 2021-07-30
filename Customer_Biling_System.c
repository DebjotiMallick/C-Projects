 #include<stdio.h>
 #include<conio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<windows.h>

 void input();
 void writefile();
 void search();
 void del();
 void output();
 FILE *ft, *fp;
 char ch;

 struct date{
	   int month;
	   int day;
	   int year;
	   };

  struct account {
	char name[100];
	int number;
	int acct_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
  }customer;
  int tl,sl,ts;
 int main()
	{
	  int i,n;
	  printf("\n\n\n\n\n\n\t  CUSTOMER BILLING SYSTEM:\n\n");
	  printf("\t===============================\n");
	  printf("\t1:    Add new customer account\n");
	  printf("\t2:    Search customer account\n");
	  printf("\t3:    Delete customer account\n");
	  printf("\t4:    Exit\n");
	  printf("\t================================\n");
	  do{
	       printf("\n\tEnter correct choice : ");
	       ch=getche();
	  }while(ch<='0' || ch>'4');
	  switch(ch){
		case '1':
            input();
            if(customer.payment>0)
                customer.acct_type=(customer.payment<0.1*customer.oldbalance)? 'O': 'D';
            else
                customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
            customer.newbalance=customer.oldbalance - customer.payment;
            writefile();
			main();
		case '2':
			search();
			ch=getche();
			main();
		case '3':
			del();
			main();
		case '4':
			system("cls");
			printf("\n\n\n\n\t\t----------CLOSING WINDOW------------");
			Sleep(2000);
			exit(0);
	  }
	  return 0;

 }


   void input()
	{
	  FILE *fp=fopen("data.dat","r");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\n\tCustomer no: %d\n", ++customer.number);
	  fclose(fp);
	  printf("\tAccount number: ");
	  scanf("%d",&customer.acct_no);
	  printf("\n\tName: ");
	  scanf("%s",customer.name);
	  printf("\n\tMobile no: ");
	  scanf("%f",&customer.mobile_no);
	  printf("\n\tStreet: ");
	  scanf("%s",customer.street);
	  printf("\n\tCity: ");
	  scanf("%s",customer.city);
	  printf("\n\tPrevious balance: ");
	  scanf("%f",&customer.oldbalance);
	  printf("\n\tCurrent payment: ");
	  scanf("%f",&customer.payment);
	  printf("\n\tPayment date(dd/mm/yyyy): ");
	  scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	  system("cls");
	  return;
   }

   void writefile()
   {
	  fp=fopen("data.dat","a");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
   }

   void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("data.dat","r");
	 do{
		fseek(fp,0,SEEK_END);
		tl=ftell(fp);
		sl=sizeof(customer);
		ts=tl/sl;
		fseek(fp,(ts-1)*sl,SEEK_SET);
		fread(&customer,sizeof(customer),1,fp);
		n=customer.number;
		system("cls");
		printf("\n Enter customer name: ");
		scanf("%s",nam);
		fseek(fp,0,SEEK_SET);
		for(i=1;i<=n;i++){
			fread(&customer,sizeof(customer),1,fp);
			if(strcmp(customer.name,nam)==0){
				output();
				m=0;
				break;
			}
		}			
		if(m!=0)
		printf("\n\n Doesn't exist\n");
		printf("\n Another?(y/n)");
		ch=getche();
	} while(ch=='y');
	system("cls");
	fclose(fp);
	main();
	
		    
	 }


   void output()
	 {
	   printf("\n\n    Customer no    :%d\n",customer.number);
	   printf("    Name 	   :%s\n",customer.name);
	   printf("    Mobile no      :%.f\n",customer.mobile_no);
	   printf("    Account number :%d\n",customer.acct_no);
	   printf("    Street         :%s\n",customer.street);
	   printf("    City           :%s\n",customer.city);
	   printf("    Old balance    :%.2f\n",customer.oldbalance);
	   printf("    Current payment:%.2f\n",customer.payment);
	   printf("    New balance    :%.2f\n",customer.newbalance);
	   printf("    Payment date   :%d/%d/%d\n\n",customer.lastpayment.day,customer.lastpayment.month,customer.lastpayment.year);
	   printf("    Account status :");
	   switch(customer.acct_type)
	      {
	      case 'C':
		 printf("CURRENT\n\n");
		 break;
	      case 'O':
		 printf("OVERDUE\n\n");
		 break;
	      case 'D':
		 printf("DELINQUENT\n\n");
		 break;
	      default:
		 printf("ERROR\\n\n");
	      }
	      return;
	   }

void del(){
	char custname[20];
	system("cls");
    do{
		printf("Enter name of customer to delete : ");
		scanf("%s", custname);
		ft = fopen("temp.dat", "wb");
		rewind(fp);
		while(fread(&customer, sizeof(customer), 1, fp) == 1){
			if(strcmp(customer.name, custname) != 0){
				fwrite(&customer, sizeof(customer), 1, ft);
			}
		}
		fclose(fp);
		fclose(ft);
		remove("data.dat");
		rename("temp.dat", "data.dat");
		fp = fopen("data.dat", "rb+");
		printf("Delete another record ? (y/n) : ");
		fflush(stdin);
		ch = getche();
	} while(ch == 'y');
	fclose(fp);
	return;
}














