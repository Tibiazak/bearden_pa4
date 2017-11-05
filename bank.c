/*
 * Joshua Bearden
 * CS2750 PA4
 * 04/11/17
 */

#include <stdio.h>
// A struct of account type, holding name, account number and balance
typedef struct account_t{
   char fName[20];
   char initial[2];
   char lName[20];
   int accountNum;
   int accountBal;
} account_t;

int menu()
{
   int status = 0;
   printf("\n ************************\n")
   printf("Welcome to the bank!\n************************\nPlease make a selection:\n");
   printf("0: Exit\n1: Deposit\n2: Withdrawal\n3: Add Account\n");
   printf("4: Remove Account\n5: Balance Inquiry\n6: View Accounts\n");
   scanf("%i", &status);
   return status;
}

// A menu-driven banking program storing data in a binary file
int main(int argc, char** argv)
{
   //declare variables and open the file
   FILE * fp;
   account_t account;
   account_t accList[49];
   int temp_accNum;
   int temp_amt;
   int readCheck;
   int i = 0;
   int numOfAccts = 0;
   fp = fopen("accounts.dat", "ab+");
   if(fp == NULL)
   {
      printf("Failed to open the file!\n");
      return 1;
   }

   //make an array of everything in the file so far
   readCheck = fread(&account, sizeof(account_t), 1, fp);
   while( (readCheck != 0) && (i < 50) )
   {
      accList[i] = account;
      i++;
      readCheck = fread(&account, sizeof(account_t), 1, fp);
   }
   numOfAccts = i; //get the current max number of accounts

   //start the main loop
   //print menu, get user selection
   int status = menu();
   //exit program on 0
   while(status != 0)
   {
      switch(status) //switch on the option chosen
      {
         case 1: //deposit
            printf("Please enter the account number:\n");
            scanf("%i", &temp_accNum);
            for( i = 0; i < numOfAccts; i++)
            {
               if (accList[i].accountNum == temp_accNum)
               {
                  printf("Please enter the amount to deposit\n");
                  scanf("%i", &temp_amt);
                  accList[i].accountBal = temp_amt;
                  printf("Deposit successful!\n");
                  status = menu();
                  break;
               }
            }
            printf("Account number is invalid!\n");
            status = menu();
            break;
         case 2: //withdraw
            status = menu();
            break;
         case 3: //add account
            printf("Please enter the first name:\n");
            scanf("%s", &account.fName[0]);

            printf("Please enter the middle initial:\n");
            scanf("%s", &account.initial[0]);

            printf("Please enter the last name:\n");
            scanf("%s", &account.lName[0]);

            printf("Please enter the desired account number:\n");
            scanf("%i", &temp_accNum);

            if(numOfAccts != 0)
            {
               for(i = 0; i < numOfAccts; i++)
               {
                  if(accList[i].accountNum == temp_accNum)
                  {
                     printf("The account number is in use!");
                     status = menu();
                     break;
                  }
               }
            }

            printf("Please enter the initial deposit amount:\n");
            scanf("%i", &account.accountBal);
            account.accountNum = temp_accNum;

            accList[numOfAccts] = account;
            numOfAccts++;
            printf("Account added successfully!\n");
            status = menu();
            break;
         case 4: //remove account
            status = menu();
            break;
         case 5: //balance inquiry
            printf("Please enter the account number:\n");
            scanf("%i", &temp_accNum);
            for(i = 0; i < numOfAccts; i++)
            {
               if(accList[i].accountNum == temp_accNum)
               {
                  printf("The account in the name of %s %s %s with number %i has a balance of $%i\n", 
                     accList[i].fName, 
                     accList[i].initial, 
                     accList[i].lName, 
                     accList[i].accountNum, 
                     accList[i].accountBal);
                  status = menu();
                  break;
               }
            }
            printf("The account number is invalid!\n");
            status = menu();
            break;
         case 6: //view all accounts
            status = menu();
            break;
         default:
            printf("Invalid selection!");
            status = menu();
      }
   }
   fclose(fp);
   return 0;
}