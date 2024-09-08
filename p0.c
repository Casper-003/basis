#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>  
#include <stdlib.h> //引入exit函数
#include <string.h> // 引入字符串处理函数  
#include <stdbool.h>

// 定义学生信息的结构体  
struct Student
{
    char name[50];
    int id;
    float score;
};

// 定义函数来输入学生信息  
void inputStudents(struct Student students[], int* count, int maxStudents) 
{
    int i = 0;
    char choice;

    printf("现在开始录入学生成绩信息，请按提示操作。\n");
    while (i < maxStudents) 
    {
        printf("学生姓名：\n");
        scanf("%49s", students[i].name); // 使用%49s限制输入长度以防溢出  

        printf("学生学号：\n");
        scanf("%d", &students[i].id);

        printf("学生成绩：\n");
        scanf("%f", &students[i].score);

        printf("是否继续输入下一名学生的信息？（y/n）\n");
        while (scanf(" %c", &choice) != 1 || (choice != 'y' && choice != 'n')) 
        { // 读取字符并跳过空白符  
            printf("输入不符合要求，请重新输入：\n");
        }

        if (choice == 'n')
        {
            break;
        }

        i++;
    }
    *count = i+1; // 更新已输入的学生数量  
    printf("共录入%d名学生的信息。\n", i+1);
}

// 定义函数将学生的数据写入文件
void writeStudentsToFile(const struct Student students[], int count, const char* filename)
{
    printf("即将写入文件 students.txt ...\n");
    FILE* file = fopen(filename, "w"); // 打开文件以写入，如果文件不存在则创建  
    if (file == NULL) 
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE); // 如果无法打开文件，则退出程序  
    }

    for (int i = 0; i < count; i++) 
    {
        // 将学生信息写入文件  
        fprintf(file, "%s %d %.2f\n", students[i].name, students[i].id, students[i].score);
    }

    fclose(file); // 关闭文件  
    printf("学生信息已成功写入 %s 文件。\n", filename);
    
}

// 定义函数读取文件内容
void readAndDisplayStudentsFromFile(const char* filename) 
{
    printf("读取文件内容 ...\n");
    FILE* file = fopen(filename, "r"); // 打开文件以读取  
    if (file == NULL) 
    {
        perror("Failed to open file");
        exit(EXIT_FAILURE); // 如果无法打开文件，则退出程序  
    }

    char buffer[1024]; // 创建一个足够大的缓冲区来存储每行内容  
    while (fgets(buffer, sizeof(buffer), file) != NULL) 
    {
        // 去除可能存在的换行符  
        buffer[strcspn(buffer, "\n")] = 0;

        // 打印读取到的每行内容  
        printf("%s\n", buffer); // 加上换行符以清晰分隔每个学生的信息  
    }

    fclose(file); // 关闭文件  
}

// 定义函数按成绩排序
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
                // 交换学生信息  
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("排序后的学生信息：\n");
    for (int i = 0; i < count; i++)
    {
        printf("姓名：%s\t学号：%d\t成绩：%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// 定义函数按学号排序
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
                // 交换学生信息  
                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("排序后的学生信息：\n");
    for (int i = 0; i < count; i++)
    {
        printf("姓名：%s\t学号：%d\t成绩：%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// 定义函数来根据学生姓名检索学生信息  
bool findStudentByName(const struct Student students[], int count, const char* nameToFind)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, nameToFind) == 0) 
        {
            printf("找到学生信息：\n");
            printf("姓名：%s\t学号：%d\t成绩：%.2f\n", students[i].name, students[i].id, students[i].score);
            return true; // 找到匹配项，返回true  
        }
    }
    printf("未找到名为%s的学生信息。\n", nameToFind);
    return false; // 未找到匹配项，返回false  
}

// 定义函数修改和删除学生信息
void modifyOrDeleteStudent(struct Student students[], int* count, const char* nameToFind)
{
    bool found = false;
    int index = -1;

    // 查找学生  
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
        printf("未找到名为%s的学生信息。\n", nameToFind);
        return;
    }

    char choice;
    printf("找到学生信息，是否删除该学生（d）或修改成绩（m）？\n");
    while (scanf(" %c", &choice) != 1 || (choice != 'd' && choice != 'm'))
    {
        printf("输入不符合要求，请重新输入（d/m）：\n");
    }

    if (choice == 'd') { // 删除学生  
        for (int i = index; i < *count - 1; i++)
        {
            students[i] = students[i + 1];
        }
        (*count)--;
        printf("学生信息已删除。\n");
    }
    else if (choice == 'm') 
    { // 修改成绩  
        float newScore;
        printf("请输入新的成绩：\n");
        scanf("%f", &newScore);
        students[index].score = newScore;
        printf("学生成绩已更新。\n");
    }
    printf("更新后的学生信息：\n");
    for (int i = 0; i < *count; i++)
    {
        printf("姓名：%s\t学号：%d\t成绩：%.2f\t\n", students[i].name, students[i].id, students[i].score);
    }
}

// 定义函数按分数段统计成绩信息
void countScoreRanges(const struct Student students[], int count, int scoreRanges[5])
{
    // 初始化分数段计数器  
    for (int i = 0; i < 5; i++) 
    {
        scoreRanges[i] = 0;
    }

    // 遍历学生数组，统计每个分数段的人数  
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
    // 打印每个分数段的学生数量  
    printf("分数段统计：\n");
    printf("0-59: %d\n", scoreRanges[0]);
    printf("60-69: %d\n", scoreRanges[1]);
    printf("70-79: %d\n", scoreRanges[2]);
    printf("80-89: %d\n", scoreRanges[3]);
    printf("90-100: %d\n", scoreRanges[4]);
}

int main()
{
    const char* filename = "students.txt";
    struct Student students[50]; // 假设最多有50名学生   
    int count = 0; // 已输入的学生数量   
    char nameToFind[50];
    int key = 0;

    while (1) 
    { // 使用while循环来不断显示功能选择菜单  
        printf("学生成绩管理系统\n");
        printf("0. 退出\n");
        printf("1. 输入学生信息\n");
        printf("2. 输出至文件\n");
        printf("3. 从文件读取\n");
        printf("4. 按成绩排序\n");
        printf("5. 按学号排序\n");
        printf("6. 查找学生成绩信息\n");
        printf("7. 修改或删除学生信息\n");
        printf("8. 按分数段统计成绩\n");
        printf("键入功能编号以进入对应功能（输入0退出）\n");
        scanf("%d", &key);

        switch (key)
        {
        case 0: // 退出程序  
            printf("退出学生成绩管理系统。\n");
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
            printf("请输入要查找的学生姓名：\n");
            scanf("%49s", nameToFind);
            findStudentByName(students, count, nameToFind);
            break;

        case 7:
            printf("请输入要修改或删除的学生姓名：\n");
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
            printf("无效的功能编号，请重新输入。\n");
        }
    }

    return 0;
}