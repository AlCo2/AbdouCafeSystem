#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void welcome(){
    printf("\t\t\t\t\t-----------------------\n");
    printf("\t\t\t\t\t|welcome to Abdou Cafe|\n");
    printf("\t\t\t\t\t-----------------------\n\n\n");
}
void addItem(char name[60], float price){
    int id;
    typedef struct items{
        char name[60];
        float price;
    }Item;
    Item newItem;
    for(int i=0;i<60;i++){
        newItem.name[i]=name[i];
        if(name[i]=='\0'){
            break;
        }
    }
    newItem.price = price;
    FILE *pid = fopen("id.txt", "r");
    if(pid == NULL){
        return 1;
    }
    fscanf(pid, "%d", &id);
    fclose(pid);
    FILE *fp = fopen("items.txt", "a");
    if(fp==NULL){
        return 1;
    };
    fprintf(fp, "%d-%s price: %.2f DH\n", id, newItem.name, newItem.price);
    fclose(fp);
    pid = fopen("id.txt", "w");
    id++;
    fprintf(pid, "%d", id);
    fclose(pid);
    FILE *pname = fopen("Iname.txt", "a");
    FILE *pprice = fopen("Iprice.txt", "a");
    if(pname == NULL || pprice == NULL){
        return 1;
    }
    fprintf(pname, "%s\n", newItem.name);
    fprintf(pprice, "%.2f\n", newItem.price);
    fclose(pname);
    fclose(pprice);
}
void showItems(){
    FILE *fp0 = fopen("items.txt", "r");
    if(fp0 == NULL){
        return 1;
    }
    char *evrything;
    fscanf(fp0, "%[^EOF]s",evrything);
    printf("%s", evrything);
    fclose(fp0);
}
void editItem(int id){
    int line;
    float price;
    char name[60];
    char newtext[1000], newname[1000], newprice[1000];
    int count = 0, count1 = 0, count2 = 0;
    line = id;
    printf("New name: ");
    scanf("%s", name);
    printf("price: ");
    scanf("%f", &price);
    FILE *fp = fopen("items.txt", "r");
    FILE *fnewp = fopen("newitem.txt", "w");
    FILE *pname = fopen("Iname.txt", "r");
    FILE *pprice = fopen("Iprice.txt", "r");
    FILE *pname1 = fopen("Iname1.txt", "w");
    FILE *pprice1 = fopen("Iprice1.txt", "w");
    if(pname == NULL || pprice == NULL){
        return 1;
    }
    if(pname1 == NULL || pprice1 == NULL){
        return 1;
    }
    if(fp == NULL || fnewp == NULL){
        return 1;
    }
    while((fgets(newtext, 1000, fp))!= NULL){
        fgets(newprice, 1000, pprice);
        fgets(newname, 1000, pname);
        count++;
        if(count == line){
            fprintf(fnewp, "%d-%s price: %.2f DH\n", id, name, price);
            fprintf(pprice1, "%.2f\n", price);
            fprintf(pname1, "%s\n", name);
        }
        else{
            fputs(newtext, fnewp);
            fputs(newprice, pprice1);
            fputs(newname, pname1);
        }
    }
    fclose(fp);
    fclose(fnewp);
    fclose(pprice);
    fclose(pname);
    fclose(pprice1);
    fclose(pname1);
    remove("items.txt");
    rename("newitem.txt", "items.txt");
    remove("Iprice.txt");
    rename("Iprice1.txt", "Iprice.txt");
    remove("Iname.txt");
    rename("Iname1.txt", "Iname.txt");
}
void deleteAll(){
    FILE *fp = fopen("id.txt", "w");
    if(fp==NULL){
        return 1;
    }
    fprintf(fp, "1");
    fclose(fp);
    remove("items.txt");
    remove("Iname.txt");
    remove("Iprice.txt");
}
void deleteItem(int id){
    int count = 0;
    int line;
    char newtext[1000], newname[1000], newprice[1000];
    line = id;
    FILE *fp = fopen("items.txt", "r");
    FILE *fnewp = fopen("newitem.txt", "w");
    FILE *pname = fopen("Iname.txt", "r");
    FILE *pprice = fopen("Iprice.txt", "r");
    FILE *pname1 = fopen("Iname1.txt", "w");
    FILE *pprice1 = fopen("Iprice1.txt", "w");
    if(fp == NULL || fnewp == NULL){
        return 1;
    }
    while((fgets(newtext, 1000, fp))!= NULL){
        fgets(newprice, 1000, pprice);
        fgets(newname, 1000, pname);
        count++;
        if(count == line){
            fprintf(fnewp, "%d-\n", id);
            fprintf(pprice1, "\n");
            fprintf(pname1, "\n");
        }
        else{
            fputs(newtext, fnewp);
            fputs(newname, pname1);
            fputs(newprice, pprice1);
        }
    }
    fclose(fp);
    fclose(fnewp);
    fclose(pprice);
    fclose(pname);
    fclose(pprice1);
    fclose(pname1);
    remove("items.txt");
    rename("newitem.txt", "items.txt");
    remove("Iprice.txt");
    rename("Iprice1.txt", "Iprice.txt");
    remove("Iname.txt");
    rename("Iname1.txt", "Iname.txt");
}

float total(int id, int q);
float getprice(int id);
int main()
{
    int choix, start, choix1;
    start = 1;
    while(start)
    {
    start:
    printf("\n");
    welcome();
    printf("==========================================================================\n");
    printf("1-Items\n2-make a facture\n3-stop the App\n\n");
    printf("take a choice: ");
    scanf("%d", &choix);
    switch(choix){
    case 1:
        printf("==========================================================================\n");
            printf("1-Add Item\n2-Edit Item\n3-Delete Item\n4-Show items\n5-Back\n");
            printf("take a choice: ");
            scanf("%d", &choix1);
        switch(choix1){
            char name[60];
            int itemId;
            float price;
            case 1:
                printf("name of the item: ");
                scanf("%s", name);
                printf("price: ");
                scanf("%f", &price);
                addItem(name, price);
                printf("---------------------------");
                printf("%s added succesfuly", name);
                printf("---------------------------");
                break;
            case 2:
                showItems();
                printf("number of the item: ");
                scanf("%d", &itemId);
                editItem(itemId);
                printf("---------------------------");
                printf("item number %d eddited succesfuly", itemId);
                printf("---------------------------");
                break;
            case 3:
                printf("1-delete 1 item\n2-delete All Item\n3-Go Back\n chose: ");
                int deleteChoice;
                scanf("%d", &deleteChoice);
                switch(deleteChoice){
                case 1:
                    printf("\n\n\n=================================================================\n==================================================\n==========\n");
                    showItems();
                    printf("-----------");
                    printf("\n item id you want to delete: ");
                    int id;
                    scanf("%d", &id);
                    deleteItem(id);
                    printf("=================================");
                    printf("\nitem number %d got deleted", id);
                    printf("\n=================================");
                    break;
                case 2:
                    printf("are you sure?\n y: yes\n n: no\n");
                    char sure;
                    scanf(" %c", &sure);
                    if(sure=='y'){
                        deleteAll();
                        break;
                    }else{
                        goto start;
                        break;
                    }
                    break;
                case 3:
                    goto start;
                    break;
                }
                break;
            case 4:
                printf("=========================\n\n");
                showItems();
                printf("\n\n=========================");
                break;
            case 5:
                goto start;
                break;
            default:
                printf("erore in choice");
                break;
        }
        break;
    case 2:
        printf("---------------------welcome to facture----------------------\n\n");
        int facStart = 1;
        int q, itemChoice;
        int n = 0;
        float totali;
        float totalall = 0;
        FILE *fp1 = fopen("facture.txt", "w");
        if(fp1 == NULL){
            return 1;
        }
        fprintf(fp1 ,"----------------------------------------------------\n");
        fprintf(fp1 ,"|                *Abdou Facture*                   |\n");
        fprintf(fp1 ,"|                                                  |\n");
        int idInfac = 1;
        float totalfac = 0;
        while(facStart){
            printf("\n~~~~~~~~~~~~~~~");
            printf("\n");
            showItems();
            printf("\n~~~~~~~~~~~~~~~\n");
            printf("enter 0 to stop\n chose item id: ");
            scanf("%d", &itemChoice);
            if(itemChoice==0){
                printf("DONE!");
                break;
            }
            printf("quantite: ");
            scanf("%d", &q);
            totali = total(itemChoice, q);
            printf("%           ====================       price:%.2fDH       ====================            \n", totali);
            int line;
            line = itemChoice;
            int count = 0;
            char namex[100];
            FILE *fname = fopen("Iname.txt", "r");
            if(fname == NULL){
                return 1;
                }
            while(fscanf(fname, "%s", namex)!= NULL){
                count++;
                if(count == line){
                    break;
                    }
                }
            fclose(fname);
            float pricex = getprice(itemChoice);
            fprintf(fp1 ,"|        %d- %d*%.2f %s         ",idInfac, q,pricex ,namex);
            fprintf(fp1, "%.2fDH\n", totali);
            totalfac+=totali;
            idInfac++;
        }
        fprintf(fp1 ,"|                                                  |\n");
        fprintf(fp1 ,"|                              total: %.2fDH      |\n", totalfac);
        fprintf(fp1, "----------------------------------------------------");
        fclose(fp1);
        break;
    case 3:
        start=0;
        break;
    default:
        printf("error in choix!!\n");
        break;
    }
    }
    return 0;
}
float total(int id, int q){
    int line;
    line = id;
    int count = 0;
    float price;
    FILE *fprice = fopen("Iprice.txt", "r");
    if(fprice == NULL){
        return 1;
    }
    while(fscanf(fprice, "%f", &price)!= NULL){
        count++;
        if(count == line){
            break;
        }
    }
    fclose(fprice);
    return price * q;
}
float getprice(int id){
    int line;
    line = id;
    int count = 0;
    float price;
    FILE *fprice = fopen("Iprice.txt", "r");
    if(fprice == NULL){
        return 1;
    }
    while(fscanf(fprice, "%f", &price)!= NULL){
        count++;
        if(count == line){
            break;
        }
    }
    fclose(fprice);
    return price;
}
