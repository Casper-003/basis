#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h> //����exit����
#include <string.h> // �����ַ���������  
#include <stdbool.h>

// ����ѧ����Ϣ�Ľṹ��  
struct Student
{
    char name[50];
    int id;
    float score;
};

// ���庯��������ѧ����Ϣ  
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

        printf("ѧ���ɼ���\n");
        scanf("%f", &students[i].score);

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
    *count = i+1; // �����������ѧ������  
    printf("��¼��%d��ѧ������Ϣ��\n", i+1);
}

// ���庯����ѧ��������д���ļ�
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
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].id, students[i].score);
    }

    fclose(file); // �ر��ļ�  
    printf("ѧ����Ϣ�ѳɹ�д�� %s �ļ���\n", filename);
    
}

// ���庯����ȡ�ļ�����
void readAndDisplayStudentsFromFile(const char* filename) 
{
    printf("��ȡ�ļ����� ...\n");
    FILE* file = fopen(filename, "r"); // ���ļ��Զ�ȡ  
    if (file == NULL) 
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE); // ����޷����ļ������˳�����  
    }

    char buffer[1024]; // ����һ���㹻��Ļ��������洢ÿ������  
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        // ȥ�����ܴ��ڵĻ��з�  
        buffer[strcspn(buffer, "\n")] = 0;

        // ��ӡ��ȡ����ÿ������  
        printf("%s\n", buffer); // ���ϻ��з��������ָ�ÿ��ѧ������Ϣ  
    }

    fclose(file); // �ر��ļ�  
}

// ���庯�����ɼ�����
void sortStudentsByScore(struct Student students[], int count) 
{
    int i, j;
    struct Student temp;
    for (i = 0; i < count - 1; i++) 
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (students[j].score < students[j + 1].score) 
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
        printf("������%s\tѧ�ţ�%d\t�ɼ���%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// ���庯����ѧ������
void sortStudentsById(struct Student students[], int count)
{
    int i, j;
    struct Student temp;
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
        printf("������%s\tѧ�ţ�%d\t�ɼ���%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// ���庯��������ѧ����������ѧ����Ϣ  
bool findStudentByName(const struct Student students[], int count, const char* nameToFind)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, nameToFind) == 0) 
        {
            printf("�ҵ�ѧ����Ϣ��\n");
            printf("������%s\tѧ�ţ�%d\t�ɼ���%.2f\n", students[i].name, students[i].id, students[i].score);
            return true; // �ҵ�ƥ�������true  
        }
    }
    printf("δ�ҵ���Ϊ%s��ѧ����Ϣ��\n", nameToFind);
    return false; // δ�ҵ�ƥ�������false  
}

// ���庯���޸ĺ�ɾ��ѧ����Ϣ
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

    char choice;
    printf("�ҵ�ѧ����Ϣ���Ƿ�ɾ����ѧ����d�����޸ĳɼ���m����\n");
    while (scanf(" %c", &choice) != 1 || (choice != 'd' && choice != 'm'))
    {
        printf("���벻����Ҫ�����������루d/m����\n");
    }

    if (choice == 'd') { // ɾ��ѧ��  
        for (int i = index; i < *count - 1; i++)
        {
            students[i] = students[i + 1];
        }
        (*count)--;
        printf("ѧ����Ϣ��ɾ����\n");
    }
    else if (choice == 'm') 
    { // �޸ĳɼ�  
        float newScore;
        printf("�������µĳɼ���\n");
        scanf("%f", &newScore);
        students[index].score = newScore;
        printf("ѧ���ɼ��Ѹ��¡�\n");
    }
    printf("���º��ѧ����Ϣ��\n");
    for (int i = 0; i < *count; i++)
    {
        printf("������%s\tѧ�ţ�%d\t�ɼ���%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// ���庯����������ͳ�Ƴɼ���Ϣ
void countScoreRanges(const struct Student students[], int count, int scoreRanges[5])
{
    // ��ʼ�������μ�����  
    for (int i = 0; i < 5; i++) 
    {
        scoreRanges[i] = 0;
    }

    // ����ѧ�����飬ͳ��ÿ�������ε�����  
    for (int i = 0; i < count; i++) {
        if (students[i].score >= 0 && students[i].score < 60) 
        {
            scoreRanges[0]++;
        }
        else if (students[i].score >= 60 && students[i].score < 70) 
        {
            scoreRanges[1]++;
        }
        else if (students[i].score >= 70 && students[i].score < 80) 
        {
            scoreRanges[2]++;
        }
        else if (students[i].score >= 80 && students[i].score < 90) 
        {
            scoreRanges[3]++;
        }
        else if (students[i].score >= 90 && students[i].score <= 100) 
        {
            scoreRanges[4]++;
        }
    }
    // ��ӡÿ�������ε�ѧ������  
    printf("������ͳ�ƣ�\n");
    printf("0-59: %d\n", scoreRanges[0]);
    printf("60-69: %d\n", scoreRanges[1]);
    printf("70-79: %d\n", scoreRanges[2]);
    printf("80-89: %d\n", scoreRanges[3]);
    printf("90-100: %d\n", scoreRanges[4]);
}

int main()
{
    const char* filename = "students.txt";
    struct Student students[50]; // ���������50��ѧ��   
    int count = 0; // �������ѧ������   
    char nameToFind[50];
    int key = 0;

    while (1) 
    { // ʹ��whileѭ����������ʾ����ѡ��˵�  
        printf("ѧ���ɼ�����ϵͳ\n");
        printf("0. �˳�\n");
        printf("1. ����ѧ����Ϣ\n");
        printf("2. ������ļ�\n");
        printf("3. ���ļ���ȡ\n");
        printf("4. ���ɼ�����\n");
        printf("5. ��ѧ������\n");
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
            readAndDisplayStudentsFromFile(filename);
            break;

        case 4:
            sortStudentsByScore(students, count);
            break;

        case 5:
            sortStudentsById(students, count);
            break;

        case 6:
            printf("������Ҫ���ҵ�ѧ��������\n");
            scanf("%49s", nameToFind);
            findStudentByName(students, count, nameToFind);
            break;

        case 7:
            printf("������Ҫ�޸Ļ�ɾ����ѧ��������\n");
            scanf("%49s", nameToFind);
            if (findStudentByName(students, count, nameToFind)) {
                modifyOrDeleteStudent(students, &count, nameToFind);
            }
            break;

        case 8:
        {
            int scoreRanges[5];
            countScoreRanges(students, count, scoreRanges);
            break;
        }

        default:
            printf("��Ч�Ĺ��ܱ�ţ����������롣\n");
        }
    }

    return 0;
}