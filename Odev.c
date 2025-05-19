#include <stdio.h>

#define FILE_NAME "file.dat"

struct ogr {
    int id;
    char name[100];
    float price;
    int stock;
};

void showMenu();

void addProduct();

void updateProduct();

void getProducts();

void deleteProduct();

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    printf("\n------Welcome to the Ogr System------\n");
    while (1) {
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Show Products\n");
        printf("5. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                getProducts();
                break;
            case 5:
                return;
                break;
            default:
                printf("Invalid Choice! \n");
                break;
        }
    }
}

void addProduct() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("File not found! \n");
        return;
    }

    struct ogr one;
    printf("Enter id: \n");
    scanf("%d", &one.id);
    printf("Enter name: \n");
    scanf("%s", one.name);
    printf("Enter price: \n");
    scanf("%f", &one.price);
    printf("Enter stock: \n");
    scanf("%d", &one.stock);

    if (fwrite(&one, sizeof(struct ogr), 1, file) == 1) {
        printf("Added successful!..\n");
    } else {
        printf("Error! \n");
    }
    fclose(file);
}


void updateProduct() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("File not found! \n");
        return;
    }
    struct ogr one;
    int id, found=0;

    printf("Enter id Update: \n");
    scanf("%d", &id);

    while (fread(&one, sizeof(struct ogr), 1, file)) {
        if (one.id == id) {
            printf("Currently Stock: %d\n", one.stock);
            printf("Enter new stock: \n");
            scanf("%d", &one.stock);

            fseek(file, -sizeof(struct ogr), SEEK_CUR);
            fwrite(&one, sizeof(struct ogr), 1, file);
            printf("Updated successful!..\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Error! \n");
    }
    fclose(file);
}

void getProducts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("File not found! \n");
        return;
    }
    struct ogr one;
    int id, found = 0;

    printf("Enter id: \n");
    scanf("%d", &id);
    while (fread(&one, sizeof(struct ogr), 1, file)) {
        if (one.id == id) {
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", one.id, one.name, one.price, one.stock);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Error! \n");
    }
    fclose(file);
}

void deleteProduct() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("File not found! \n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        printf("File not found! \n");
        fclose(file);
        return;
    }

    struct ogr one;
    int id, found = 0;

    printf("Enter id: \n");
    scanf("%d", &id);

    while (fread(&one, sizeof(struct ogr), 1, file)) {
        if (one.id == id) {
            found = 1;
            continue;
        }
        fwrite(&one, sizeof(struct ogr), 1, temp);
    }
    fclose(file);
    fclose(temp);
    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Deleted Successful! \n");
    }else {
        remove("temp.dat");
        printf("Error!..\n");
    }
}
