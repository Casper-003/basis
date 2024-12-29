#define _CRT_SECURE_NO_WARNINGS
#define MAX_STUDENTS 50 
#define MAX_NAME_LENGTH 50  
#define SCORE_RANGES 11  // 0-100分，每10分一个段，共11个段  

#include <stdio.h>  
#include <stdlib.h> //引入exit函数
#include <string.h> // 引入字符串处理函数  
#include <stdbool.h>//引入布尔类型

// √ 定义学生信息的结构体  
struct Student
{
    char name[MAX_NAME_LENGTH];
    int id;
    float score1;
    float score2;
    float score3;
};

// √ 定义函数来输入学生信息  
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

        printf("学生第一科成绩：\n");
        scanf("%f", &students[i].score1);

        printf("学生第二科成绩：\n");
        scanf("%f", &students[i].score2);

        printf("学生第三科成绩：\n");
        scanf("%f", &students[i].score3);

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
    *count = i + 1; // 更新已输入的学生数量  
    printf("共录入%d名学生的信息。\n", i + 1);
}

// √ 定义函数将学生的数据写入文件
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
        fprintf(file, "%s %d %.2f %.2f %.2f\n", students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
    }

    fclose(file); // 关闭文件  
    printf("学生信息已成功写入 %s 文件。\n", filename);

}

// √ 定义函数实现从文件读取功能
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
    // 由于我们传递了相同的指针（即&count），这里不需要额外的操作  
}

// √ 定义函数实现排序功能
void sortStudentsByScore(struct Student students[], int count)
{
    int choice;
    int i, j;
    struct Student temp;
    printf("输入数字以选择你想排序的方式：\n1.按第一门成绩  2.按第二门成绩  3.按第三门成绩  4.按三门总成绩  5.按三门平均成绩  6.按学号\n");
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\t总成绩：%.2f\n",
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\t平均成绩：%.2f\n",
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
            printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
        }
        break;

    default:
        printf("无效的功能编号，请重新输入。\n");
    }

}

// √ 定义函数来根据学生姓名检索学生信息  
bool findStudentByName(const struct Student students[], int count, const char* nameToFind)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(students[i].name, nameToFind) == 0)
        {
            printf("找到学生信息：\n");
            printf("姓名：%s\t学号：%d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
                students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
            return true; // 找到匹配项，返回true  
        }
    }
    printf("未找到名为%s的学生信息。\n", nameToFind);
    return false; // 未找到匹配项，返回false  
}

// √ 定义函数修改和删除学生信息
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


    char choice0;
    printf("找到学生信息，是否删除该学生（d）或修改成绩（m）？\n");
    while (scanf(" %c", &choice0) != 1 || (choice0 != 'd' && choice0 != 'm'))
    {
        printf("输入不符合要求，请重新输入（d/m）：\n");
    }

    if (choice0 == 'd') { // 删除学生  
        for (int i = index; i < *count - 1; i++)
        {
            students[i] = students[i + 1];
        }
        (*count)--;
        printf("学生信息已删除。\n");
    }
    else if (choice0 == 'm')
    { // 修改成绩  
        int choice1;
        printf("选择要修改的科目（1=第一科，2=第二科，3=第三科）：\n");
        scanf("%d", &choice1);

        float newScore;
        printf("请输入新的成绩：\n");
        scanf("%f", &newScore);

        switch (choice1)
        {
        case 1: students[index].score1 = newScore; break;
        case 2: students[index].score2 = newScore; break;
        case 3: students[index].score3 = newScore; break;
        default: printf("无效的科目选择。\n");
        }
        printf("学生成绩已更新。\n");
    }
    printf("更新后的学生信息：\n");
    for (int i = 0; i < *count; i++)
    {
        printf("姓名：%-10s\t学号：%3d\t第一科成绩：%.2f\t第二科成绩：%.2f\t第三科成绩：%.2f\n",
            students[i].name, students[i].id, students[i].score1, students[i].score2, students[i].score3);
    }
}

// 定义函数分析学生成绩分布段
void analyzeScoreDistribution(const struct Student students[], int count) {
    int scoreRanges[3][11] = { 0 }; // [科目][分数段(0-100分，每10分一段)]  
    for (int i = 0; i < count; i++) {
        int idx1 = students[i].score1 / 10; // 计算第一科成绩的分数段索引  
        int idx2 = students[i].score2 / 10; // 计算第二科成绩的分数段索引  
        int idx3 = students[i].score3 / 10; // 计算第三科成绩的分数段索引  
        if (idx1 < 10) scoreRanges[0][idx1]++;
        if (idx2 < 10) scoreRanges[1][idx2]++;
        if (idx3 < 10) scoreRanges[2][idx3]++;
    }

    // 输出分析结果  
    printf("第一科成绩分布：\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[0][i] > 0) {
            printf("%d0-%d9: %d人\n", i, i + 1, scoreRanges[0][i]);
        }
    }
    printf("第二科成绩分布：\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[1][i] > 0) {
            printf("%d0-%d9: %d人\n", i, i + 1, scoreRanges[1][i]);
        }
    }
    printf("第三科成绩分布：\n");
    for (int i = 0; i < 10; i++) {
        if (scoreRanges[2][i] > 0) {
            printf("%d0-%d9: %d人\n", i, i + 1, scoreRanges[2][i]);
        }
    }
}

int main()
{
    const char* filename = "students.txt";
 // 假设最多有50名学生   
    int count = 0; // 已输入的学生数量   
    char nameToFind[50];
    int key = 0;
    struct Student students[MAX_STUDENTS]; // 在这里也需要加上 struct 关键字  

    while (1)
    { // 使用while循环来不断显示功能选择菜单  
        printf("学生成绩管理系统\n");
        printf("0. 退出\n");
        printf("1. 输入学生信息\n");
        printf("2. 输出至文件\n");
        printf("3. 从文件读取\n");
        printf("4. 按成绩排序\n");
        printf("5. 展示内存的内容\n");
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
            printf("请输入要查找的学生姓名：\n");
            scanf("%49s", nameToFind);
            findStudentByName(students, count, nameToFind);
            break;

        case 7:
            printf("请输入要修改或删除的学生姓名：\n");
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
            printf("无效的功能编号，请重新输入。\n");
        }
    }

    return 0;
}