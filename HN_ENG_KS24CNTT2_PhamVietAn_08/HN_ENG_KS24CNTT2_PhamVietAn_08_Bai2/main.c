#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[50];
    int age;
    struct Student *left;
    struct Student *right;
}Student;

Student *createStudent(int id, char *name, int age) {
    Student *stu = (Student *)malloc(sizeof(Student));
    stu->id = id;
    strcpy(stu->name, name);
    stu->age = age;
    stu->left = NULL;
    stu->right = NULL;
    return stu;
}

Student *addStudent(Student *root, int id, char *name, int age) {
    if (root == NULL) {
        return createStudent(id, name, age);
    }
    if (id < root->id) {
        root->left = addStudent(root->left, id, name, age);
    } else if (id > root->id) {
        root->right = addStudent(root->right, id, name, age);
    }
    return root;
}

void inorder(Student *root) {
    if (root) {
        inorder(root->left);
        printf("ID: %d | Name: %s | AGE: %d\n",root->id, root->name, root->age);
        inorder(root->right);
    }
}

Student *searchStudent(Student *root, int id) {
    if (!root || root->id == id) {
        return root;
    }
    if (id < root->id) {
        return searchStudent(root->left, id);
    } else {
        return searchStudent(root->right, id);
    }
}

int main(void) {
    Student *root = NULL;
    char command[50];
    int id, age;
    char name[50];
    int choice;
    do {
        printf("---------- STUDENT MANAGER ----------\n");
        printf("1. Them sinh vien\n");
        printf("2. Hien thi danh sach sinh vien\n");
        printf("3. Tim kiem sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Nhap ID sinh vien: ");
                scanf("%d", &id);
                getchar();
                printf("Nhap ten sinh vien: ");
                fgets(name, 50, stdin);
                name[strcspn(name, "\n")] = '\0';
                printf("Nhap tuoi sinh vien: ");
                scanf("%d", &age);
                getchar();

                root = addStudent(root, id, name, age);
                printf("Da them sinh vien\n");
                break;

            case 2:
                if (!root) {
                    printf("Danh sach trong\n");
                } else {
                    printf("---------- Danh sach sinh vien ----------\n");
                    inorder(root);
                }
                break;

            case 3:
                printf("Nhap id sinh vien can tim kiem:");
                scanf("%d", &id);
                getchar();

                Student *stu = searchStudent(root, id);
                if (stu) {
                    printf("Sinh vien theo ID: %d | NAME: %s | AGE: %d \n",stu->id, stu->name, stu->age);
                } else {
                    printf("Khong tim thay sinh vien\n");
                }
                break;

            case 4:
                break;

            case 5:
                printf("Thoat chuong trinh\n");
                break;

            default:
                printf("Lua chon khong hop le\n");
        }
    } while (choice != 5);
    return 0;
}