#define _CRT_SECURE_NO_WARNINGS
#define MAX_STUDENTS 50 
#define MAX_NAME_LENGTH 50  
#define SCORE_RANGES 11  // 0-100�֣�ÿ10��һ���Σ���11����  

#include <stdio.h>  
#include <stdlib.h> //����exit����
#include <string.h> // �����ַ���������  
#include <stdbool.h>//���벼������

// �� ����ѧ����Ϣ�Ľṹ��  
struct Student
{
    char name[MAX_NAME_LENGTH];
    int id;
    float score1;
    float score2;
    float score3;
};

// �� ���庯��������ѧ����Ϣ  
void inputStudents(struct Student students[], int* count, int maxStudents)
{
    int i = 0;
    char choice;

    printf("���ڿ�ʼ¼��ѧ���ɼ���Ϣ���밴��ʾ������\n");
    while (i < maxStudents)
    {
        printf("ѧ��������\n");
        scanf("%49s", students[i].name); // ʹ��%49s�������볤���Է����  

        printf("ѧ��ѧ�ţ�\n");
        scanf("%d", &students[i].id);

        printf("ѧ����һ�Ƴɼ���\n");
        scanf("%f", &students[i].score1);

        printf("ѧ���ڶ��Ƴɼ���\n");
        scanf("%f", &students[i].score2);

        printf("ѧ�������Ƴɼ���\n");
        scanf("%f", &students[i].score3);

        printf("�Ƿ����������һ��ѧ������Ϣ����y/n��\n");
        while (scanf(" %c", &choice) != 1 || (choice != 'y' && choice != 'n'))
        { // ��ȡ�ַ��������հ׷�  
            printf("���벻����Ҫ�����������룺\n");
        }

        if (choice == 'n')
        {
            break;
        }

        i++;
    }
    *count = i + 1; // �����������ѧ������  
    printf("��¼��%d��ѧ������Ϣ��\n", i + 1);
}

// �� ���庯����ѧ��������д���ļ�
void writeStudentsToFile(const struct Student students[], int count, const char* filename)
{
    printf("����д���ļ� students.txt ...\n");
    FILE* file = fopen(filename, "w"); // ���ļ���д�룬����ļ��������򴴽�  
    if (file == NULL)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE); // ����޷����ļ������˳�����  
    }

    for (int i = 0; i < count; i++)
    {
        // ��ѧ����Ϣд���ļ�  
        fprintf(file, "%s %d %.2f %.2f %.2f\n", students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
    }

    fclose(file); // �ر��ļ�  
    printf("ѧ����Ϣ�ѳɹ�д�� %s �ļ���\n", filename);

}

// �� ���庯��ʵ�ִ��ļ���ȡ����
void readStudentsFromFile(const char* filename, struct Student* students, int* numStudents) 
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    *numStudents = 0;
    while (fscanf(file, "%49s %d %f %f %f", students[*numStudents].name, &students[*numStudents].id, &students[*numStudents].score1, &students[*numStudents].score2, &students[*numStudents].score3) == 5)
    {
        (*numStudents)++;
        if (*numStudents >= MAX_STUDENTS)
        {
            fprintf(stderr, "Exceeded maximum number of students\n");
            break;
        }
    }
    fclose(file);
    // �������Ǵ�������ͬ��ָ�루��&count�������ﲻ��Ҫ����Ĳ���  
}

// �� ���庯��ʵ��������
void sortStudentsByScore(struct Student students[], int count)
{
    int choice;
    int i, j;
    struct Student temp;
    printf("����������ѡ����������ķ�ʽ��\n1.����һ�ųɼ�  2.���ڶ��ųɼ�  3.�������ųɼ�  4.�������ܳɼ�  5.������ƽ���ɼ�  6.��ѧ��\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (students[j].score1 < students[j + 1].score1)
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
        }
        break;

    case 2:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (students[j].score2 < students[j + 1].score2)
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
        }
        break;

    case 3:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (students[j].score3 < students[j + 1].score3)
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
        }
        break;

    case 4:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if ((students[j].score1 + students[j].score2 + students[j].score3 ) < (students[j+1].score1 + students[j+1].score2 + students[j+1].score3))
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\t�ܳɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3, students[i].score1 + students[i].score2 + students[i].score3);
        }
        break;

    case 5:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if ((students[j].score1 + students[j].score2 + students[j].score3) / 3 < (students[j+1].score1 + students[j+1].score2 + students[j+1].score3) / 3)
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\tƽ���ɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3, (students[i].score1 + students[i].score2 + students[i].score3) / 3);
        }
        break;

    case 6:
        for (i = 0; i < count - 1; i++)
        {
            for (j = 0; j < count - i - 1; j++)
            {
                if (students[j].id > students[j + 1].id)
                {
                    // ����ѧ����Ϣ  
                    temp = students[j];
                    students[j] = students[j + 1];
                    students[j + 1] = temp;
                }
            }
        }
        printf("������ѧ����Ϣ��\n");
        for (int i = 0; i < count; i++)
        {
            printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
        }
        break;

    default:
        printf("��Ч�Ĺ��ܱ�ţ����������롣\n");
    }

}

// �� ���庯��������ѧ����������ѧ����Ϣ  
bool findStudentByName(const struct Student students[], int count, const char* nameToFind)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, nameToFind) == 0)
        {
            printf("�ҵ�ѧ����Ϣ��\n");
            printf("������%s\tѧ�ţ�%d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
            return true; // �ҵ�ƥ�������true  
        }
    }
    printf("δ�ҵ���Ϊ%s��ѧ����Ϣ��\n", nameToFind);
    return false; // δ�ҵ�ƥ�������false  
}

// �� ���庯���޸ĺ�ɾ��ѧ����Ϣ
void modifyOrDeleteStudent(struct Student students[], int* count, const char* nameToFind)
{
    bool found = false;
    int index = -1;

    // ����ѧ��  
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(students[i].name, nameToFind) == 0)
        {
            found = true;
            index = i;
            break;
        }
    }

    if (!found)
    {
        printf("δ�ҵ���Ϊ%s��ѧ����Ϣ��\n", nameToFind);
        return;
    }


    char choice0;
    printf("�ҵ�ѧ����Ϣ���Ƿ�ɾ����ѧ����d�����޸ĳɼ���m����\n");
    while (scanf(" %c", &choice0) != 1 || (choice0 != 'd' && choice0 != 'm'))
    {
        printf("���벻����Ҫ�����������루d/m����\n");
    }

    if (choice0 == 'd') { // ɾ��ѧ��  
        for (int i = index; i < *count - 1; i++)
        {
            students[i] = students[i + 1];
        }
        (*count)--;
        printf("ѧ����Ϣ��ɾ����\n");
    }
    else if (choice0 == 'm')
    { // �޸ĳɼ�  
        int choice1;
        printf("ѡ��Ҫ�޸ĵĿ�Ŀ��1=��һ�ƣ�2=�ڶ��ƣ�3=�����ƣ���\n");
        scanf("%d", &choice1);

        float newScore;
        printf("�������µĳɼ���\n");
        scanf("%f", &newScore);

        switch (choice1)
        {
        case 1: students[index].score1 = newScore; break;
        case 2: students[index].score2 = newScore; break;
        case 3: students[index].score3 = newScore; break;
        default: printf("��Ч�Ŀ�Ŀѡ��\n");
        }
        printf("ѧ���ɼ��Ѹ��¡�\n");
    }
    printf("���º��ѧ����Ϣ��\n");
    for (int i = 0; i < *count; i++)
    {
        printf("������%-10s\tѧ�ţ�%3d\t��һ�Ƴɼ���%.2f\t�ڶ��Ƴɼ���%.2f\t�����Ƴɼ���%.2f\n",
            students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
    }
}

// ���庯������ѧ���ɼ��ֲ���
void analyzeScoreDistribution(const struct Student students[], int count) {
    int scoreRanges[3][11] = { 0 }; // [��Ŀ][������(0-100�֣�ÿ10��һ��)]  
    for (int i = 0; i < count; i++) {
        int idx1 = students[i].score1 / 10; // �����һ�Ƴɼ��ķ���������  
        int idx2 = students[i].score2 / 10; // ����ڶ��Ƴɼ��ķ���������  
        int idx3 = students[i].score3 / 10; // ��������Ƴɼ��ķ���������  
        if (idx1 < 10) scoreRanges[0][idx1]++;
        if (idx2 < 10) scoreRanges[1][idx2]++;
        if (idx3 < 10) scoreRanges[2][idx3]++;
    }

    // ����������  
    printf("��һ�Ƴɼ��ֲ���\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[0][i] > 0) {
            printf("%d0-%d9: %d��\n", i, i + 1, scoreRanges[0][i]);
        }
    }
    printf("�ڶ��Ƴɼ��ֲ���\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[1][i] > 0) {
            printf("%d0-%d9: %d��\n", i, i + 1, scoreRanges[1][i]);
        }
    }
    printf("�����Ƴɼ��ֲ���\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[2][i] > 0) {
            printf("%d0-%d9: %d��\n", i, i + 1, scoreRanges[2][i]);
        }
    }
}

int main()
{
    const char* filename = "students.txt";
 // ���������50��ѧ��   
    int count = 0; // �������ѧ������   
    char nameToFind[50];
    int key = 0;
    struct Student students[MAX_STUDENTS]; // ������Ҳ��Ҫ���� struct �ؼ���  

    while (1)
    { // ʹ��whileѭ����������ʾ����ѡ��˵�  
        printf("ѧ���ɼ�����ϵͳ\n");
        printf("0. �˳�\n");
        printf("1. ����ѧ����Ϣ\n");
        printf("2. ������ļ�\n");
        printf("3. ���ļ���ȡ\n");
        printf("4. ���ɼ�����\n");
        printf("5. չʾ�ڴ������\n");
        printf("6. ����ѧ���ɼ���Ϣ\n");
        printf("7. �޸Ļ�ɾ��ѧ����Ϣ\n");
        printf("8. ��������ͳ�Ƴɼ�\n");
        printf("���빦�ܱ���Խ����Ӧ���ܣ�����0�˳���\n");
        scanf("%d", &key);

        switch (key)
        {
        case 0: // �˳�����  
            printf("�˳�ѧ���ɼ�����ϵͳ��\n");
            return 0;

        case 1:
            inputStudents(students, &count, 50);
            break;

        case 2:
            writeStudentsToFile(students, count, filename);
            break;

        case 3:
            readStudentsFromFile(filename, students, &count);
            break;

        case 4:
            sortStudentsByScore(students, count);
            break;

        case 5:
            for (int i = 0; i < count; i++)
            {
                printf("Name: %s, ID: %d, Grade1: %.2f, Grade2: %.2f, Grade3: %.2f\n",
                    students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
            }
            break;

        case 6:
            printf("������Ҫ���ҵ�ѧ��������\n");
            scanf("%49s", nameToFind);
            findStudentByName(students, count, nameToFind);
            break;

        case 7:
            printf("������Ҫ�޸Ļ�ɾ����ѧ��������\n");
            scanf("%49s", nameToFind);
            if (findStudentByName(students, count, nameToFind))
            {
                modifyOrDeleteStudent(students, &count, nameToFind);
            }
            break;

        case 8:
        {
            analyzeScoreDistribution(students, count);
            break;
        }

        default:
            printf("��Ч�Ĺ��ܱ�ţ����������롣\n");
        }
    }

    return 0;
}