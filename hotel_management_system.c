#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_ROOMS 10
#define RATE 1000

struct Reservation
{
int room;
char name[40];
char phone[15];
int days;
};

void bookRoom(struct Reservation *r);
void viewRooms();
void checkout();
int isBooked(int room);
int loadBookings(struct Reservation arr[]);
void saveBooking(struct Reservation *r);

int main()
{
int ch;

printf("\n===== HOTEL MANAGEMENT SYSTEM =====\n");

while(1)
{
printf("\n1. Book Room");
printf("\n2. View All Bookings");
printf("\n3. Checkout");
printf("\n4. Exit");
printf("\nEnter choice : ");
scanf("%d",&ch);

switch(ch)
{
case 1:
{
struct Reservation r;
bookRoom(&r);
break;
}
case 2: viewRooms(); break;
case 3: checkout(); break;
case 4: exit(0);
default: printf("Wrong choice\n");
}
}
}

void bookRoom(struct Reservation *r)
{
printf("Enter room number (1-%d): ",TOTAL_ROOMS);
scanf("%d",&r->room);
getchar();

if(r->room < 1 || r->room > TOTAL_ROOMS)
{
printf("Invalid Room\n");
return;
}

if(isBooked(r->room))
{
printf("Room already booked\n");
return;
}

printf("Enter Name: ");
fgets(r->name,40,stdin);
r->name[strcspn(r->name,"\n")] = 0;

printf("Enter Phone: ");
fgets(r->phone,15,stdin);
r->phone[strcspn(r->phone,"\n")] = 0;

printf("Days: ");
scanf("%d",&r->days);

saveBooking(r);
printf("Booking Success\n");
}

void saveBooking(struct Reservation *r)
{
FILE *fp = fopen("hotel.dat","ab");
if(fp==NULL)
{
printf("File error\n");
return;
}
fwrite(r,sizeof(*r),1,fp);
fclose(fp);
}

int isBooked(int room)
{
struct Reservation r;
FILE *fp = fopen("hotel.dat","rb");

if(fp==NULL) return 0;

while(fread(&r,sizeof(r),1,fp))
{
if(r.room == room)
{
fclose(fp);
return 1;
}
}

fclose(fp);
return 0;
}

int loadBookings(struct Reservation arr[])
{
FILE *fp = fopen("hotel.dat","rb");
int count = 0;

if(fp==NULL) return 0;

while(fread(&arr[count],sizeof(arr[count]),1,fp))
{
count++;
}

fclose(fp);
return count;
}

void viewRooms()
{
struct Reservation arr[100];
int n = loadBookings(arr);

if(n == 0)
{
printf("No bookings found\n");
return;
}

printf("\n---- BOOKINGS ----\n");
for(int i=0;i<n;i++)
{
printf("\nRoom : %d",arr[i].room);
printf("\nName : %s",arr[i].name);
printf("\nPhone : %s",arr[i].phone);
printf("\nDays : %d",arr[i].days);
printf("\nBill : Rs.%d",arr[i].days * RATE);
printf("\n---------------");
}
}

void checkout()
{
struct Reservation arr[100];
int n = loadBookings(arr);
int room, found = 0;

FILE *fp = fopen("hotel.dat","wb");
if(fp==NULL) return;

printf("Enter room number to checkout: ");
scanf("%d",&room);

for(int i=0;i<n;i++)
{
if(arr[i].room == room)
{
printf("\nFinal Bill = Rs.%d\n",arr[i].days * RATE);
found = 1;
}
else
{
fwrite(&arr[i],sizeof(arr[i]),1,fp);
}
}

fclose(fp);

if(found)
printf("Checkout Done\n");
else
printf("Room not found\n");
}

