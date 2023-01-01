#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int calculateBill(int units);
void displayBill(int customerId, int month, int year);
void saveBill(int customerId, int month, int year, int units, int bill);
char *generateFileName(int customerId, int month, int year);
void modifyBill(int customerId, int month, int year);

static char *months[] = {"January", "February", "March", "April",
                            "May", "June", "July", "August", "September",
                            "October", "November", "December"};

int main() {
	// Logic to generate Electricity Billing Application goes here
    int option;

    printf("Electricity Billing App\n");
    printf("-----------------------\n\n");
    printf("1 - Generate Electricity Bill\n");
    printf("2 - Display Electricity Bill\n");
    printf("3 - Modify Electricity Bill\n");
    printf("4 - Exit\n\n");

    while(1) { // 1 = true, 0 = false
        printf("Select any option: ");
        scanf("%d", &option);
        int customerId, month, year, units;
        // Perform user selected operation
        switch(option) {
            case 1:
                // generate bill
                printf("Customer ID: ");
                scanf("%d", &customerId);
                printf("Month: ");
                scanf("%d", &month);
                if(month < 1 || month > 12) {
                    printf("Invalid value for month!\n");
                    break;
                }
                printf("Year: ");
                scanf("%d", &year);
                printf("Units Consumed: ");
                scanf("%d", &units);
                if(units < 0) {
                    printf("Invalid value for units!\n");
                    break;
                }
                int totalBill = calculateBill(units);
                printf("Bill for the month of %s, %d for Customer - %d is Rs. %d\n", months[month-1], year, customerId, totalBill);
                // generate bill file
                saveBill(customerId, month, year, units, totalBill);
                break;
            case 2:
                // display bill
                printf("Customer ID: ");
                scanf("%d", &customerId);
                printf("Month: ");
                scanf("%d", &month);
                if(month < 1 || month > 12) {
                    printf("Invalid value for month!\n");
                    break;
                }
                printf("Year: ");
                scanf("%d", &year);
                displayBill(customerId, month, year);
                break;
            case 3:
                // modify bill
                printf("Customer ID: ");
                scanf("%d", &customerId);
                printf("Month: ");
                scanf("%d", &month);
                if(month < 1 || month > 12) {
                    printf("Invalid value for month!\n");
                    break;
                }
                printf("Year: ");
                scanf("%d", &year);
                printf("Checking the existing bill information...\n");
                displayBill(customerId, month, year);
                int confirm;
                printf("Do you want to modify this bill? Type 1(Yes) or 2(No): ");
                //confirm = getch();
                scanf("%d", &confirm);
                if(confirm == 1) {
                    modifyBill(customerId, month, year);
                } else {
                    // do Nothing
                }
                break;
            case 4:
                // exit the program
                return 0;
                break;
            default:
                printf("Invalid Option! Select a valid option.\n");
        }
    }
}



char *generateFileName(int customerId, int month, int year) {
    char *fileName = malloc(30*sizeof(char));
    char temp[10];
    sprintf(temp, "%d", customerId);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", month);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", year);
    strcat(fileName, temp);
    strcat(fileName, ".txt");

    return fileName;
}

// Formula to calculate Electricity Bill
// Units: 1-100       : Rs.1 per unit
// Units: 101-500     : Rs.2 per unit
// Units: 501 & above : Rs.3 per unit
// For example, If Units consumed are 550, bill value will be (100*1) + (400*2) + (50*3) = Rs. 950

int calculateBill(int units) {
	// Logic to calculate the electricity bill goes here
    int totalBill = 0;
    if(units>100) {
        totalBill += 1*100;
        units = units - 100;
        if(units > 400) {
            totalBill += 2*400;
            units = units - 400;
            totalBill += 3*units;
        } else {
            totalBill += 2*units;
        }
    } else {
        totalBill += 1*units;
    }

    return totalBill;
}

void displayBill(int customerId, int month, int year) {
	// Logic to print the electricity bill for the customer for the given month and year goes here
    char *fileName = generateFileName(customerId, month, year);
    printf("FileName is: %s\n", fileName);
    char filePath[100] = "E:\\Work\\Upgrad\\C Programming Practice\\SampleProject\\";
    strcat(filePath, fileName);
    FILE *fptr = fopen(filePath, "r");
    if(fptr == NULL) {
        printf("Not Found! Electricity Bill for the given Customer and Month is not generated yet!\n");
        return;
    }

    char line[20];
    // while(fscanf(fptr, "%s", line) != EOF) {
    //     printf("Line is: %s\n", line);
    // }
    fscanf(fptr, "%s", line);
    fscanf(fptr, "%s", line);
    fscanf(fptr, "%s", line);
    fscanf(fptr, "%s", line);
    printf("Units Consumed: %s\n", line);
    fscanf(fptr, "%s", line);
    printf("Bill for the month of %s, %d for Customer - %d is Rs. %s\n", months[month-1], year, customerId, line);

    fclose(fptr);
}

void saveBill(int customerId, int month, int year, int units, int bill) {
	// Logic to save the electricity bill into a file goes here
    char *fileName = generateFileName(customerId, month, year);
    printf("FileName is: %s\n", fileName);
    FILE *fptr = fopen(fileName, "w");
    char temp[20];
    sprintf(temp, "%d", customerId);
    fprintf(fptr, temp);
    fprintf(fptr, "\n");
    sprintf(temp, "%d", month);
    fprintf(fptr, temp);
    fprintf(fptr, "\n");
    sprintf(temp, "%d", year);
    fprintf(fptr, temp);
    fprintf(fptr, "\n");
    sprintf(temp, "%d", units);
    fprintf(fptr, temp);
    fprintf(fptr, "\n");
    sprintf(temp, "%d", bill);
    fprintf(fptr, temp);
    fprintf(fptr, "\n");
    printf("Bill generated successfully\n");
    fclose(fptr);
}

void modifyBill(int customerId, int month, int year) {
    int units;
    printf("Updated Units Consumed: ");
    scanf("%d", &units);
    if(units < 0) {
        printf("Invalid value for units!\n");
        return;
    }
    int totalBill = calculateBill(units);
    printf("Updated Bill for the month of %d, %d for Customer - %d is Rs. %d\n", month, year, customerId, totalBill);
    // generate bill file
    saveBill(customerId, month, year, units, totalBill);
}