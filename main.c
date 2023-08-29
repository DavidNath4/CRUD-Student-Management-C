#include <stdio.h>
#include <stdlib.h>

typedef struct student {
  int id;
  char name[20];
  int nilai;

} student;

void create() {
  student *s;
  FILE *fp;
  int n, i, j;
  printf("==================CREATE NEW DATA==================\n");
  printf("How many Input : ");
  scanf("%d", &n);

  s = (student *)calloc(n, sizeof(student));
  fp = fopen("data.txt", "w");

  for (int i = 0; i < n; i++) {
    printf("\nEnter IDNo: ");
    scanf("%d", &s[i]);
    fflush(stdin);
    printf("Enter Name: ");
    scanf("%[^\n]s", s[i].name);
    printf("Enter Nilai: ");
    scanf("%d", &s[i].nilai);

    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================CREATE NEW DATA==================\n");
  fclose(fp);
}

void display() {
  student sl;
  FILE *fp;
  fp = fopen("data.txt", "r");

  printf("==================DISPLAY DATA==================\n");
  while (fread(&sl, sizeof(student), 1, fp)) {
    printf("%-4d%-20s%d\n", sl.id, sl.name, sl.nilai);
  }
  printf("==================DISPLAY DATA==================\n");
  fclose(fp);
}

void append() {
  student *s;
  FILE *fp;
  int n, i, j;
  printf("==================INSERT DATA==================\n");
  printf("How many Input : ");
  scanf("%d", &n);

  s = (student *)calloc(n, sizeof(student));
  fp = fopen("data.txt", "a");

  for (int i = 0; i < n; i++) {
    printf("\nEnter IDNo: ");
    scanf("%d", &s[i]);
    fflush(stdin);
    printf("Enter Name: ");
    scanf("%[^\n]s", s[i].name);
    printf("Enter Nilai: ");
    scanf("%d", &s[i].nilai);

    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================INSERT DATA==================\n");
  fclose(fp);
}

void number_of_record() {
  student sl;
  FILE *fp;
  fp = fopen("data.txt", "r");
  fseek(fp, 0, SEEK_END);
  int n = ftell(fp) / sizeof(student);
  printf("==================RECORDED DATA==================\n");
  printf("\nNO OF RECORDS = %d\n\n", n);
  printf("==================RECORDED DATA==================\n");
  fclose(fp);
}

void search() {
  student sl;
  FILE *fp;
  int j, id, flag = 0;
  fp = fopen("data.txt", "r");

  printf("==================SEARCH DATA==================\n");
  printf("ENTER ID : ");
  scanf("%d", &id);
  while (fread(&sl, sizeof(student), 1, fp)) {
    if (sl.id == id) {
      flag = 1;
      printf("%-4d%-20s%d\n", sl.id, sl.name, sl.nilai);
    }
  }
  if (!flag) {
    printf("DATA NOT FOUND!\n");
  }
  printf("==================SEARCH DATA==================\n");
  fclose(fp);
}

// UPDATE DATA FUNCTION
void update() {
  student sl;
  FILE *fp, *fpTemp;
  int j, id, flag = 0;
  fp = fopen("data.txt", "r");
  fpTemp = fopen("temp.txt", "w");

  printf("==================UPDATE DATA==================\n");
  printf("ENTER ID TO UPDATE: ");
  scanf("%d", &id);
  while (fread(&sl, sizeof(student), 1, fp)) {
    if (sl.id == id) {
      flag = 1;
      fflush(stdin);
      printf("Enter New Name: ");
      scanf("%[^\n]s", sl.name);
      printf("Enter Nilai: ");
      scanf("%d", &sl.nilai);
    }
    fwrite(&sl, sizeof(student), 1, fpTemp);
  }
  fclose(fp);
  fclose(fpTemp);
  if (flag) {
    fpTemp = fopen("temp.txt", "r");
    fp = fopen("data.txt", "w");

    while (fread(&sl, sizeof(student), 1, fpTemp)) {
      fwrite(&sl, sizeof(student), 1, fp);
    }

    fclose(fp);
    fclose(fpTemp);
  } else {
    printf("DATA NOT FOUND!\n");
  }
  printf("==================UPDATE DATA==================\n");
}

void delete() {
  student sl;
  FILE *fp, *fpTemp;
  int j, id, flag = 0;
  fp = fopen("data.txt", "r");
  fpTemp = fopen("temp.txt", "w");

  printf("==================DELETE DATA==================\n");
  printf("ENTER ID TO DELETE: ");
  scanf("%d", &id);
  while (fread(&sl, sizeof(student), 1, fp)) {
    if (sl.id == id) {
      flag = 1;
    } else {
      fwrite(&sl, sizeof(student), 1, fpTemp);
    }
  }
  fclose(fp);
  fclose(fpTemp);

  if (flag) {
    fpTemp = fopen("temp.txt", "r");
    fp = fopen("data.txt", "w");

    while (fread(&sl, sizeof(student), 1, fpTemp)) {
      fwrite(&sl, sizeof(student), 1, fp);
    }
    printf("DATA DELETED!\n");
    fclose(fp);
    fclose(fpTemp);
  } else {
    printf("DATA NOT FOUND!\n");
  }
  printf("==================DELETE DATA==================\n");
}

void sort_in_file_asc() {
  student *s, sl;
  FILE *fp;
  int i, j;
  fp = fopen("data.txt", "r");
  fseek(fp, 0, SEEK_END);
  int n = ftell(fp) / sizeof(student);

  s = (student *)calloc(n, sizeof(student));

  rewind(fp);
  for (i = 0; i < n; i++) {
    fread(&s[i], sizeof(student), 1, fp);
  }
  fclose(fp);

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (s[i].nilai > s[j].nilai) {
        sl = s[i];
        s[i] = s[j];
        s[j] = sl;
      }
    }
  }

  fp = fopen("data.txt", "w");

  printf("==================SORTED IN DATA (By nilai)==================\n");
  for (i = 0; i < n; i++) {
    printf("%-4d%-20s%d\n", s[i].id, s[i].name, s[i].nilai);
    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================SORTED IN DATA (By nilai)==================\n");

  fclose(fp);
}

void sort_in_file_desc() {
  student *s, sl;
  FILE *fp;
  int i, j;
  fp = fopen("data.txt", "r");
  fseek(fp, 0, SEEK_END);
  int n = ftell(fp) / sizeof(student);

  s = (student *)calloc(n, sizeof(student));

  rewind(fp);
  for (i = 0; i < n; i++) {
    fread(&s[i], sizeof(student), 1, fp);
  }
  fclose(fp);

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (s[i].nilai < s[j].nilai) {
        sl = s[i];
        s[i] = s[j];
        s[j] = sl;
      }
    }
  }

  fp = fopen("data.txt", "w");

  printf("==================SORTED IN DATA (By nilai)==================\n");
  for (i = 0; i < n; i++) {
    printf("%-4d%-20s%d\n", s[i].id, s[i].name, s[i].nilai);
    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================SORTED IN DATA (By nilai)==================\n");

  fclose(fp);
}

void sort_in_file_by_id_asc() {
  student *s, sl;
  FILE *fp;
  int i, j;
  fp = fopen("data.txt", "r");
  fseek(fp, 0, SEEK_END);
  int n = ftell(fp) / sizeof(student);

  s = (student *)calloc(n, sizeof(student));

  rewind(fp);
  for (i = 0; i < n; i++) {
    fread(&s[i], sizeof(student), 1, fp);
  }
  fclose(fp);

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (s[i].id > s[j].id) {
        sl = s[i];
        s[i] = s[j];
        s[j] = sl;
      }
    }
  }

  fp = fopen("data.txt", "w");

  printf("==================SORTED IN DATA (By ID)==================\n");
  for (i = 0; i < n; i++) {
    printf("%-4d%-20s%d\n", s[i].id, s[i].name, s[i].nilai);
    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================SORTED IN DATA (By ID)==================\n");

  fclose(fp);
}

void sort_in_file_by_id_desc() {
  student *s, sl;
  FILE *fp;
  int i, j;
  fp = fopen("data.txt", "r");
  fseek(fp, 0, SEEK_END);
  int n = ftell(fp) / sizeof(student);

  s = (student *)calloc(n, sizeof(student));

  rewind(fp);
  for (i = 0; i < n; i++) {
    fread(&s[i], sizeof(student), 1, fp);
  }
  fclose(fp);

  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (s[i].id < s[j].id) {
        sl = s[i];
        s[i] = s[j];
        s[j] = sl;
      }
    }
  }

  fp = fopen("data.txt", "w");

  printf("==================SORTED IN DATA (By ID)==================\n");
  for (i = 0; i < n; i++) {
    printf("%-4d%-20s%d\n", s[i].id, s[i].name, s[i].nilai);
    fwrite(&s[i], sizeof(student), 1, fp);
  }
  printf("==================SORTED IN DATA (By ID)==================\n");

  fclose(fp);
}

int main() {
  int ch;
  do {
    printf("\n==================MAIN MENU==================");
    printf("\n1. CREATE");
    printf("\n2. DISPLAY");
    printf("\n3. APPEND");
    printf("\n4. NO OF RECORDS");
    printf("\n5. SEARCH");
    printf("\n6. UPDATE");
    printf("\n7. DELETE");
    printf("\n8. SORTING DATA - TOTAL NILAI ASC");
    printf("\n9. SORTING DATA - TOTAL NILAI DESC");
    printf("\n10. SORTING DATA - ID ASC");
    printf("\n11. SORTING DATA - ID DESC");
    printf("\n0. EXIT");

    printf("\nINPUT THE NUMBER  ");
    scanf("%d", &ch);
    system("cls");
    switch (ch) {
      case 1:
        create();
        break;
      case 2:
        display();
        break;
      case 3:
        append();
        break;
      case 4:
        number_of_record();
        break;
      case 5:
        search();
        break;
      case 6:
        update();
        break;
      case 7:
        delete ();
        break;
      case 8:
        sort_in_file_asc();
        break;
      case 9:
        sort_in_file_desc();
        break;
      case 10:
        sort_in_file_by_id_asc();
        break;
      case 11:
        sort_in_file_by_id_desc();
        break;
    }

  } while (ch != 0);

  return 0;
}
