#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void set_up();
void draw();
void logic();
void main_interface();
void print_highscore();
void play();
void highscore_update();
void highscore_initialize();
void help();
void settings();
void navigation();

int i, j, height = 20, width = 20,speed=0.5;
int gameover, score;
int x, y, fruitx, fruity, flag;


void main()
{
    highscore_initialize();

    char c;

    navigation();

    while(1)
    {
        main_interface();

        printf("  --> ");
        fflush(stdin);
        scanf(" %c",&c);

        if(c=='1')
        {
            play();
        }
        else if(c=='2')
        {
            print_highscore();
        }
        else if(c=='3')
        {
            help();
        }
        else if(c=='4')
        {
            settings();
        }
        else if(c=='e')
        {
            return;
        }
        else
        {
            system("cls");
            printf("\tINVALID INPUT\n\n");
        }
    }

}



void setup()
{
    srand(time(NULL));
	gameover = 0;

	x = height / 2;
	y = width / 2;

label1:
	fruitx = rand() % 20;
	if (fruitx == 0)
		goto label1;
label2:
	fruity = rand() % 20;
	if (fruity == 0)
		goto label2;
	score = 0;
}

void draw()
{
	system("cls");
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (i == 0 || i == width - 1
				|| j == 0
				|| j == height - 1) {
				printf("#");
			}
			else {
				if (i == x && j == y)
					printf("0");
				else if (i == fruitx
						&& j == fruity)
					printf("*");
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	printf("Score : %d",score);

}

void input()
{
	if (kbhit()) {
		switch (getch()) {
		case 'a':
			flag = 1;
			break;
		case 's':
			flag = 2;
			break;
		case 'd':
			flag = 3;
			break;
		case 'w':
			flag = 4;
			break;
		case 'x':
			gameover = 1;
			break;
		}
	}
}


void logic()
{
	sleep(speed);
	switch (flag) {
	case 1:
		y--;
		break;
	case 2:
		x++;
		break;
	case 3:
		y++;
		break;
	case 4:
		x--;
		break;
	default:
		break;
	}

	if (x <= 0 || x >= height
		|| y <= 0 || y >= width)
		gameover = 1;

	if (x == fruitx && y == fruity) {
	label3:
		fruitx = rand() % 20;
		if (fruitx == 0)
			goto label3;

	label4:
		fruity = rand() % 20;
		if (fruity == 0)
			goto label4;
		score += 10;
	}
}

void main_interface()
{
    printf("1 --> play\n");
    printf("2 --> Highscore\n");
    printf("3 --> Help\n");
    printf("4 --> settings\n");
    return;
}

void play()
{
    char c;

    setup();

	while (!gameover)
    {
		draw();
		input();
		logic();
	}

    highscore_update();

	while(1)
    {
        printf("\n--> ");
        fflush(stdin);
        scanf(" %c",&c);
        if(tolower(c)=='h')
        {
            system("cls");
            return;
        }
        else if(tolower(c)=='e')
        {
            exit(0);
        }
    }
}

void print_highscore()
{
    char c;

    FILE *file = fopen("highscore.txt","r");

    while((c=fgetc(file))!=EOF)
    {
        printf("%c",c);
    }
    fclose(file);

    while(1)
    {
        printf("  --> ");
        fflush(stdin);
        scanf(" %c",&c);
        if(tolower(c)=='h')
        {
            system("cls");
            return;
        }
        else if(tolower(c)=='e')
        {
            exit(0);
        }
    }

    return;
}

void highscore_update()
{
    FILE* file = fopen("highscore.txt","r");
    char c;
    char* tmp=malloc(sizeof(char));
    int i = 0;

    while((c=fgetc(file))!=EOF)
    {
        tmp[i]=c;
        i++;
        tmp = realloc(tmp,sizeof(char));
    }
    tmp[i]='\0';

    int highscore = atoi(tmp);

    if(score>highscore)
    {
        printf("\n\tYAYY!! YOU HAVE DONE BEST SCORE\n");
        fclose(file);
        FILE* file = fopen("highscore.txt","w");
        fprintf(file,"%d",score);
        fclose(file);
    }
    else
    {
        fclose(file);
    }
    return;
}

void highscore_initialize()
{
    FILE* file = fopen("highscore.txt","r");
    if(file==NULL)
    {
        fclose(file);
        FILE*file= fopen("highscore.txt","w");
        fprintf(file,"0");
        fclose(file);
    }
    else
    {
        fclose(file);
        return;
    }
}

void help()
{
    printf("Use 'a' , 's' , 'd' , 'w' to move the snake left, down, right and upwards.\n");
    printf("Eat the fruits represented as '*' within the box to increase your score.\n");
    printf("Avoid hitting the walls of the box. If you do it will result in a game over.\n");
    printf("Press 'h' to go back to the main interface.\n");
}

void settings()
{
    char c;

    printf("1 --> EASY MODE\n");
    printf("2 --> HARD MODE\n");

    while(1)
    {
        fflush(stdin);
        printf("  --> ");
        scanf(" %c",&c);

        if(c=='1')
        {
            speed=1;
            return;
        }
        else if(c=='2')
        {
            speed=0.5;
            return;
        }
        else if(tolower(c)=='h')
        {
            return;
        }
        else if(tolower(c)=='e')
        {
            exit(0);
        }
        else
        {
            printf("INVALID INPUT\n");
        }
    }

}

void navigation()
{
    printf("\tNAVIGATION:\n\tENTER 1,2,3... TO CHOOSE ANY OPTION\n\t'e' --> exit\n\t'h' --> home\n\n");
}
