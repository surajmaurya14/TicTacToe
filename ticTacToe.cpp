#include <stdio.h>
#include <stdlib.h>
struct Stack
{
    int size;
    int top;
    int *S;
};
void create(struct Stack *st)
{
    printf("Enter No of Games To Be Played: \n");
    scanf("%d", &st->size);
    st->top = -1;
    st->S = (int *)malloc(st->size * sizeof(int));
}
void Display(struct Stack st)
{
    int i;
    for (i = st.top; i >= 0; i--)
    {
        if (st.S[i] == 0)
            printf("Match TIED\n");
        else
        {
            printf("Player: %d was Winner\n", st.S[i]);
        }
    }
    printf("\n");
}
void push(struct Stack *st, int x)
{
    if (st->top == st->size - 1)
        printf("Tournament Over\n");
    else
    {
        st->top++;
        st->S[st->top] = x;
    }
}
int pop(struct Stack *st)
{
    int x = -1;

    if (st->top == -1)
        printf("No Games Played\n");
    else
    {
        x = st->S[st->top--];
    }
    return x;
}
int peek(struct Stack st, int index)
{
    int x = -1;
    if (st.top - index + 1 < 0)
        printf("Invalid Index \n");
    x = st.S[st.top - index + 1];

    return x;
}
int isEmpty(struct Stack st)
{
    if (st.top == -1)
        return 1;
    return 0;
}
int isFull(struct Stack st)
{
    return st.top == st.size - 1;
}
int stackTop(struct Stack st)
{
    if (!isEmpty(st))
        return st.S[st.top];
    return -1;
}
char data[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
int player = 1;
char value = 'X';

void clear()
{
    system("clear");
}
void update()
{
    clear();
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j < 3)
                printf("| ");
            if (data[k] == ' ')
                printf("- ");
            else
                printf("%c ", data[k]);
            k++;
            if (j == 2)
                printf("| ");
        }
        printf("\n");
    }
    printf("\n");
}
int check()
{
    if (data[0] == data[1] && data[1] == data[2] && data[0] != ' ')
        return 1;

    else if (data[3] == data[4] && data[4] == data[5] && data[3] != ' ')
        return 1;

    else if (data[6] == data[7] && data[7] == data[8] && data[6] != ' ')
        return 1;

    else if (data[0] == data[3] && data[3] == data[6] && data[0] != ' ')
        return 1;

    else if (data[1] == data[4] && data[4] == data[7] && data[1] != ' ')
        return 1;

    else if (data[2] == data[5] && data[5] == data[8] && data[2] != ' ')
        return 1;

    else if (data[0] == data[4] && data[4] == data[8] && data[0] != ' ')
        return 1;

    else if (data[2] == data[4] && data[4] == data[6] && data[2] != ' ')
        return 1;

    else
    {
        int c = 0;
        for (int i = 0; i < 9; i++)
        {
            if (data[i] == ' ')
            {
                c = 1;
                break;
            }
        }
        if (c == 0)
            return 0;
        else
            return -1;
    }
}
void input()
{
    int x, i;
    player = 1;
    do
    {
        update();
        player = player % 2;
        if (player == 0)
        {
            player = 2;
            value = '0';
        }
        else
        {
            player = 1;
            value = 'X';
        }

        printf("Player %d: Enter your move\n", player);
        scanf("%d", &x);
        if (x > 9 || x < 0)
        {
            printf("Enter proper position:");
            getchar();
            player--;
        }
        else if (data[x - 1] != ' ')
        {
            printf("Position Occupied");
            getchar();
            player--;
        }
        else
        {
            data[x - 1] = value;
        }
        i = check();
        player++;
        getchar();
    } while (i == -1);
    player--;
}
int result()
{
    int k = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j < 3)
                printf("| ");
            if (data[k] == ' ')
                printf("-");
            else
                printf("%c", data[k]);
            k++;
            if (j == 2)
                printf("| ");
        }
        printf("\n");
    }
    if (check() == 0)
    {
        printf("TIE\n");
        return 0;
    }

    else if (check() == 1)
    {
        printf("\nPlayer %d wins\n", player);
        return player;
    }
    return 0;
}
void reset()
{
    for (int i = 0; i < 9; i++)
    {
        data[i] = ' ';
    }
}
void tournamentWinner(struct Stack s)
{
    if (isFull(s) != 1)
        printf("Tournament Not Completed");
    else
    {
        int p1 = 0, p2 = 0;
        int st = stackTop(s);
        for (int i = 0; i < st; i++)
        {
            int val = pop(&s);
            if (val == 0)
            {
            }
            else if (val == 1)
            {
                p1++;
            }
            else if (val == 2)
            {
                p2++;
            }
        }
        if (p1 == p2)
        {
            printf("Tournament Tied");
        }
        else if (p1 > p2)
        {
            printf("Player 1 Wins Tournament");
        }
        else
        {
            printf("Player 2 Wins Tournament");
        }
    }
}

int main()
{
    int c;
    struct Stack st;
    create(&st);
    while (1)
    {
        getchar();
        clear();
        printf("1.Play Game\n2.Get Previous Result\n3.Show History\n4.Tournament Winner\n5.Clear Previous Game Result\n6.Tournmanet started or not\n7.Exit\n\n");
        scanf("%d", &c);
        switch (c)
        {
        case 1:
        {
            if (isFull(st))
            {
                printf("Tournmanet Over");
                getchar();
                break;
            }
            reset();
            update();
            input();
            int x = result();
            push(&st, x);

            break;
        }
        case 2:
        {
            if (stackTop(st) == 1 || stackTop(st) == 2)
                printf("Player: %d was winner\n", stackTop(st));
            else
            {
                printf("Match Tied");
            }
            getchar();
            break;
        }
        case 3:
        {
            Display(st);
            getchar();
            break;
        }
        case 4:
        {
            tournamentWinner(st);
            getchar();
            break;
        }
        case 5:
        {
            pop(&st);
            getchar();
            break;
        }
        case 6:
        {
            if (isEmpty(st))
            {
                printf("Tournament not Started\n");
            }
            else if (isFull(st))
            {
                printf("Tournament Completed\n");
            }
            else
            {
                printf("Tournament Ongoing\n");
            }
            getchar();
            break;
        }
        case 7:
            return 0;

        default:
            return 0;
        }
    }
    return 0;
}
