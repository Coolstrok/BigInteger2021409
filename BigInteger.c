// Initializing BigInteger
#include "BigInteger.h"

struct BigInteger initialize(char *s)
{
    struct BigInteger new;
    struct node *temp;
    int i=0;
    new.head=NULL;
    new.sign=1;
    new.length=0;
    if(s[i]=='-')
    {
        new.sign=0;
        i++;
    } 
    while(s[i]!='\0')
    {
        temp=(struct node*)malloc(sizeof(struct node));
        temp->data =s[i]-48;
        temp->next=new.head;
        new.head=temp;
        i++;
    }
    truncate(new.head);
    i=length(new.head);
    new.length=i;
    
    return new;
} 

// Travarsing the BigInteger

void trav(struct node *head)
{
    if(head->next)
    {
        trav(head->next);
    }
    printf("%d", head->data);
}

void display(struct BigInteger num)
{
    if(num.head  && num.sign=='-')
        printf("-");
    if(num.head)
        trav(num.head);
}

// Code for Subtracting BigIntegers

struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger new;
    struct node *temp, *itr1, *itr2, *tail, *itr;
    int diff ;
    new.head = NULL;
    new.length = 0;
    new.sign = 1;

    if(a.sign== 1 && b.sign== 0 )
    {
        b.sign=1;
        new=add(a,b);
    }
    else if(a.sign== 0 && b.sign== 1)
    {
        a.sign=1;
        new=add(a,b);
        new.sign=0;
    }
    
    else
    {
        if(compare(a,b) == -1 )
        {
            itr1 = b.head;
            itr2 = a.head;
            new.sign = 0 ;
        }
        else if(compare(a,b) == 1 || compare(a,b) == 0)
        {
            itr1=a.head;
            itr2=b.head;
        }
        
        while(itr1 && itr2)
        {
            temp=(struct node*)malloc(sizeof(struct node));
            temp->next=NULL;
            if(itr1->data < itr2->data)
            {
                itr1->data +=10;
                itr1->next->data -=1;
            }
            diff=itr1->data - itr2->data;
            temp->data=diff;
            itr1=itr1->next;
            itr2=itr2->next;
            if(new.head==NULL)
            {
                new.head=temp;
            }
            else
            {
                tail->next=temp;
            }
            tail=temp;
        }

        while(itr1)
        {
            temp=(struct node*)malloc(sizeof(struct node));
            temp->next=NULL;
            temp->data=itr1->data;
            tail->next=temp;
            tail=temp;
            itr1=itr1->next;
        }
    }
    truncate(new.head);
    return new;
}

//Code for Adding BigIntegers

struct BigInteger add(struct BigInteger a, struct BigInteger b)
{
    struct BigInteger new;
    struct node *temp, *itr1, *itr2, *itr;
    itr1 = a.head;
    itr2 = b.head;
    int carry = 0, sum = 0;
    new.head = NULL;
    new.length = 0;
    new.sign = 1;

    if(a.sign== 1 && b.sign== 0 )
    {
        b.sign=1;
        new=sub(a,b);
    }
    else if(a.sign== 0 && b.sign== 1)
    {
        a.sign=1;
        new=sub(b,a);
        new.sign=0;
    }
    else
    {
        while (itr1 || itr2)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            sum =carry;
            if (itr1) {
                sum += itr1->data;
                itr1 = itr1->next;
            }
            if (itr2) {
                sum += itr2->data;
                itr2 = itr2->next;
            }
            temp->data = sum % 10;
            temp->next= NULL;
            carry = sum / 10;
            if(new.head==NULL)
            {
                new.head=temp;
            }

            else
            {
                itr->next=temp;
            }
            itr=temp;
            new.length += 1;
        }
        // itr=new.head;

        while (carry)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->data = carry % 10;
            carry /= 10;
            temp->next = new.head;
            new.head= temp;
            new.length += 1;
        }
    }  
    truncate(new.head);
    return new;
}

//Truncating The BigInteger

void truncate(struct node *head)
{
    struct node *temp=NULL;
    if(head->next->next!=NULL)
    {
        truncate(head->next);
    }
    if(head->next->next== NULL && head->next->data==0)
    {
        temp=head->next;
        head->next=NULL;
        free(temp);
    }
}

int compare(struct BigInteger a, struct BigInteger b)
{
    int flag=0;
    struct node *itr1 = a.head, *itr2 = b.head;
    if(a.length > b.length )
    {
        flag = 1;
    }
    else if(a.length < b.length)
    {
        flag = -1;
    }
    else
    {   
        while(itr1)
        {
            if(itr1->data > itr2->data)
            {
                flag=1;
            }
            else if(itr1->data < itr2->data)
            {
                flag=-1;
            }
            itr1=itr1->next;
            itr2=itr2->next;
        }
    }
    return flag;
}

int length(struct node *head)
{
    int i=0;
    while(head)
    {
        i++;
        head=head->next;
    }
    return i;
}


struct BigInteger mul(struct BigInteger a,struct BigInteger b)
{
    
    struct BigInteger pro;
    pro.head = NULL;
    pro.sign=1;
    pro.length=0;

    if(!a.head || !b.head)
        return pro;

    struct BigInteger temp ;
    temp.head = NULL;
    temp.length=0;
    temp.sign=1;

    int shift = 0;
    struct node * itr1 = a.head;

    while (itr1) {

        

        temp.head = NULL;
        struct node * itr2 = b.head;
        int carry = 0;
        struct node * last = temp.head;

        while (itr2 || carry) {
            int product = carry;

            if (itr2) {
                product += itr1->data * itr2->data;
                itr2 = itr2->next;
            }

            carry = product / 10;
            product %= 10;

            struct node * tempnode=(struct node *)malloc(sizeof(struct node ));
            tempnode->data=product;
            tempnode->next=NULL;

            if(!temp.head)
                temp.head=tempnode;
            else 
                last->next=tempnode;
            last=tempnode;
        }

        for (int i=0;i<shift;i++) {
            struct node * tempnode=(struct node *)malloc(sizeof(struct node ));
            tempnode->data=0;
            tempnode->next=temp.head;
            temp.head=tempnode;
        }

        if(pro.head)
            pro=add(pro,temp);
        else 
            pro=temp;    
        shift++;

        itr1=itr1->next;
    }
    if((a.sign==0)^(b.sign==0))
        pro.sign=0;
    
    zero(pro,pro.head);

    pro.length=0;
    struct node  * itr4=pro.head;
    while(itr4){
        pro.length++;
        itr4=itr4->next;
    }
    
    truncate(pro.head);
    return pro;

}





struct BigInteger div1(struct BigInteger a,struct BigInteger b)
{

    struct BigInteger quo,dif;
    quo.head   = NULL;
    quo.sign   = 1;
    quo.length = 0;

    if(!a.head || ! b.head)
        return quo;

    if((b.length==1)&&(b.head->data==0))
        return quo;

    if(((a.length==1)&&(a.head->data==0)) || (a.length<b.length)){
        quo.head   = (struct node * )malloc(sizeof(struct node));
        quo.head->data=0;
        quo.head->next=NULL;
        quo.length = 1;
        truncate(quo.head);
        return quo;
    }
    int i=0,d,q=0;
    struct node *temp=NULL,*stop=b.head;
    d = a.length - b.length;

    while(i<d){
        temp=(struct node *)malloc(sizeof(struct node ));
        temp->data = 0 ;
        temp->next = b.head;
        b.head = temp;
        i++;
    } 
    

    char asign=a.sign,bsign=b.sign;
    a.sign=b.sign=1;


    while(1){
        
        dif=sub(a,b);

        if(dif.sign ==0){
            struct node  *t;
            if(b.head!=stop){
                t = b.head;
                b.head=b.head->next;
                free(t);
                d--;
                
                t=(struct node *)malloc(sizeof(struct node ));
                t->data = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                
            }
            else{
                t=(struct node *)malloc(sizeof(struct node ));
                t->data = q;
                t->next = quo.head;
                quo.head = t;
                quo.length++;
                q=0;
                
                a.sign=asign;
                b.sign=bsign;

                if((a.sign==0)^(b.sign==0))
                    quo.sign=0;
                
                zero(quo,quo.head);

                quo.length=0;
                struct node  * itr4=quo.head;
                while(itr4){
                    quo.length++;
                    itr4=itr4->next;
                }


                truncate(quo.head);
                return quo;
            }
        }
        else{
            q++;
            a=dif;

        }
    }    
}

int zero(struct BigInteger num,struct node *n){
    if(!n)
        return 0;
    if(zero(num,n->next))
        return 1;
    else{
        if(n->next)
            free(n->next);
        n->next=NULL;
        return n->data;
    }

}
