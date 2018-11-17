#include<iostream>

using namespace std;

int main()
{
    int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,k,total=0,pos,temp,choice,rc, sysq[20][2], usq[20][2], processchoice;
    float avg_wt,avg_tat;

    cout<<"----------------------------------OS PROJECT---------------------------------------------\n";
    cout<<"Topic:\nScheduling Algorithms with Bankers Algorithm\n";
    cout<<"-----------------------------------------------------------------------------------------";
    cout<<"\nDescription:\nThe project consists of two parts, first part deals with applying scheduling on Processes\nThe second part is related to applying Bankers Algorithm to the process to ensure that there are no Deadlocks";

    while(1)
    {
        cout<<"\n\nEnter Type of Scheduling to be applied\n";
        cout<<"1: Priority Scheduling\n2: Shortest Job First\n3: Multilevel Queue\n";
        cin>>choice;
        while(choice!=1 && choice!=2 && choice!=3)
        {
            cout<<"Invalid Choice, Enter Valid Choice: ";
            cin>>choice;

        }
        if(choice==1)
        {
            cout<<"Enter Total Number of Process:";
            cin>>n;
            cout<<"\nEnter Burst Time and Priority\n";
            for(i=0; i<n; i++)
            {
                cout<<"\nP["<<i+1<<"]\n";
                cout<<"Burst Time:";
                cin>>bt[i];
                cout<<"Priority:";
                cin>>pr[i];
                p[i]=i+1;
            }
            //sorting burst time, priority and process number in ascending order using selection sort
            for(i=0; i<n; i++)
            {
                pos=i;
                for(j=i+1; j<n; j++)
                {
                    if(pr[j]<pr[pos])
                        pos=j;
                }
                temp=pr[i];
                pr[i]=pr[pos];
                pr[pos]=temp;

                temp=bt[i];
                bt[i]=bt[pos];
                bt[pos]=temp;

                temp=p[i];
                p[i]=p[pos];
                p[pos]=temp;
            }
            wt[0]=0;            //waiting time for first process is zero
            //calculate waiting time
            for(i=1; i<n; i++)
            {
                wt[i]=0;
                for(j=0; j<i; j++)
                    wt[i]+=bt[j];

                total+=wt[i];
            }
            avg_wt=total/n;      //average waiting time
            total=0;
            cout<<"The Schedule Before applying Bankers Algorithm";
            cout<<"\nProcess\t    Burst Time    \t    Priority    \tWaiting Time\tTurnaround Time";


            for(i=0; i<n; i++)
            {
                tat[i]=bt[i]+wt[i];     //calculate turnaround time
                total+=tat[i];
                cout<<"\nP["<<p[i]<<"]\t\t"<<bt[i]<<"\t\t\t "<<pr[i]<<"\t\t\t"<<wt[i]<<"\t\t"<<tat[i];
            }
            avg_tat=total/n;     //average turnaround time
            cout<<"\n\nAverage Waiting Time="<<avg_wt;
            cout<<"\nAverage Turnaround Time="<<avg_tat;

// Applying Bankers Algorithm------------------------------------------------------------------------------------------------------------------------
            cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<n; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<p[i];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<n; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];

            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<n; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<n; i++)
            {
                cout<<"\n";
                for(j=0; j<3; j++)
                {

                    cout<<alloc[i][j]<<" ";

                }

            }
            for(i=0; i<n; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<n; i++)
            {
                for(j=0; j<3; j++)
                {
                    need[i][j]=maxall[i][j]-alloc[i][j];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<n; i++)
            {
                cout<<"\n";
                for(j=0; j<3; j++)
                {
                    cout<<need[i][j]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<n)
            {
                iter++;
                if(iter==(4*n)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or there is no safe sequence";
                    break;
                }
                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<n; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(p[i]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }

                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=p[i];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;

                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<n; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<n; i++)
            {
                cout<<" "<<safeseq[i];
            }



            int vemp, xemp;
            int i=0;
            for(i=0; i<n; i++)
            {
                vemp=p[(arraypos[i])];// =p(1)=2;
                xemp=p[i];//=1
                p[i]=vemp;//=> 1=2;
                p[(arraypos[i])]=xemp;//=>2=1;


                vemp=bt[(arraypos[i])];
                xemp=bt[i];
                bt[i]=vemp;
                bt[(arraypos[i])]=xemp;


                vemp=pr[(arraypos[i])];
                xemp=pr[i];
                pr[i]=vemp;
                pr[(arraypos[i])]=xemp;

                vemp=arraypos[i];//=1
                int j=0;
                for(j=0; j<n; j++)
                {
                    if(arraypos[j]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[j];//=0
                arraypos[j]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;            //waiting time for first process will be zero

            //calculate waiting time
            for(i=1; i<n; i++)
            {
                wt[i]=0;
                for(j=0; j<i; j++)
                    wt[i]+=bt[j];

                total+=wt[i];
            }

            avg_wt=(float)total/n;      //average waiting time
            total=0;
            cout<<"\nAfter applying Bankers Algorithm";
            cout<<"\nProcess\t    Burst Time    \t    Priority    \tWaiting Time\tTurnaround Time";
            for(i=0; i<n; i++)
            {
                tat[i]=bt[i]+wt[i];     //calculate turnaround time
                total+=tat[i];
                cout<<"\nP["<<p[i]<<"]\t\t"<<bt[i]<<"\t\t\t "<<pr[i]<<"\t\t\t"<<wt[i]<<"\t\t"<<tat[i];
            }

            avg_tat=(float)total/n;     //average turnaround time
            cout<<"\n\nAverage Waiting Time="<<avg_wt;
            cout<<"\nAverage Turnaround Time="<<avg_tat;





        }
//EOS for Priority Scheduling--------------------------------------------------------------------------------------------------------------------

        else if(choice==2)
        {


            cout<<"Enter number of process:";
            cin>>n;

            cout<<"\nEnter Burst Time:\n";

            for(i=0; i<n; i++)
            {
                cout<<"\nP["<<i+1<<"]\n";
                cout<<"Burst Time:";
                cin>>bt[i];
                p[i]=i+1;           //contains process number
            }

            //sorting burst time in ascending order using selection sort
            for(i=0; i<n; i++)
            {
                pos=i;
                for(j=i+1; j<n; j++)
                {
                    if(bt[j]<bt[pos])
                        pos=j;
                }

                temp=bt[i];
                bt[i]=bt[pos];
                bt[pos]=temp;

                temp=p[i];
                p[i]=p[pos];
                p[pos]=temp;
            }

            wt[0]=0;            //waiting time for first process will be zero

            //calculate waiting time
            for(i=1; i<n; i++)
            {
                wt[i]=0;
                for(j=0; j<i; j++)
                    wt[i]+=bt[j];

                total+=wt[i];
            }

            avg_wt=(float)total/n;      //average waiting time
            total=0;

            cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
            for(i=0; i<n; i++)
            {
                tat[i]=bt[i]+wt[i];     //calculate turnaround time
                total+=tat[i];
                cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
            }

            avg_tat=(float)total/n;     //average turnaround time
            cout<<"\n\nAverage Waiting Time="<<avg_wt;
            cout<<"\nAverage Turnaround Time="<<avg_tat;




            cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<n; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<p[i];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<n; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];

            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<n; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<n; i++)
            {
                cout<<"\n";
                for(j=0; j<3; j++)
                {

                    cout<<alloc[i][j]<<" ";

                }

            }
            for(i=0; i<n; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<n; i++)
            {
                for(j=0; j<3; j++)
                {
                    need[i][j]=maxall[i][j]-alloc[i][j];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<n; i++)
            {
                cout<<"\n";
                for(j=0; j<3; j++)
                {
                    cout<<need[i][j]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<n)
            {
                iter++;
                if(iter==(4*n)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or there is no safe sequence";
                    break;
                }

                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<n; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(p[i]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }

                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=p[i];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;



                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<n; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<n; i++)
            {
                cout<<" "<<safeseq[i];
            }



            int vemp, xemp;
            int i=0;
            for(i=0; i<n; i++)
            {
                vemp=p[(arraypos[i])];// =p(1)=2;
                xemp=p[i];//=1
                p[i]=vemp;//=> 1=2;
                p[(arraypos[i])]=xemp;//=>2=1;


                vemp=bt[(arraypos[i])];// =p(1)=2;
                xemp=bt[i];//=1
                bt[i]=vemp;//=> 1=2;
                bt[(arraypos[i])]=xemp;//=>2=1;

                vemp=arraypos[i];//=1
                int j=0;
                for(j=0; j<n; j++)
                {
                    if(arraypos[j]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[j];//=0
                arraypos[j]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;            //waiting time for first process will be zero

            //calculate waiting time
            for(i=1; i<n; i++)
            {
                wt[i]=0;
                for(j=0; j<i; j++)
                    wt[i]+=bt[j];

                total+=wt[i];
            }

            avg_wt=(float)total/n;      //average waiting time
            total=0;
            cout<<"\nAfter applying Bankers Algorithm";
            cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
            for(i=0; i<n; i++)
            {
                tat[i]=bt[i]+wt[i];     //calculate turnaround time
                total+=tat[i];
                cout<<"\nP["<<p[i]<<"]\t\t  "<<bt[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
            }

            avg_tat=(float)total/n;     //average turnaround time
            cout<<"\n\nAverage Waiting Time="<<avg_wt;
            cout<<"\nAverage Turnaround Time="<<avg_tat;



        }

//EOS for Shortest Job First--------------------------------------------------------------------------------------------------------------------

        else if(choice==3)  // Multilevel queue
        {
            j=0;
            k=0;
            cout<<"----------------------------------------------------------------------------------------\n";
            cout<<"Implementing the algorithm using two queues: System Process Queue and User Process Queue\n";
            cout<<"----------------------------------------------------------------------------------------\n";
            cout<<"Enter Total Number of Process(System+User):\n";
            cin>>n;
            for(i=0; i<n; i++)
            {
                cout<<"\nP["<<i+1<<"]\n";
                cout<<"System/User Process(0/1)?: ";
                cin>>processchoice;
                while(processchoice!=0 && processchoice!=1)
                {
                    cout<<"Invalid Choice, Enter Valid Choice: ";
                    cin>>processchoice;

                }
                while(processchoice!=0 && processchoice!=1)
                {
                    cout<<"Invalid Choice, Enter Valid Choice: ";
                    cin>>processchoice;

                }
                if(processchoice==0)  // System Process
                {
                    cout<<"Enter Burst Time: ";
                    cin>>sysq[j][0];                    //Burst Time in First Element
                    sysq[j][1]=i+1;                     //Process Number in Second Element
                    j+=1;
                }
                else if(processchoice==1)  // User Process
                {
                    cout<<"Enter Burst Time: ";
                    cin>>usq[k][0];
                    usq[k][1]=i+1;
                    k+=1;
                }
            }

//SOC for System Process Queue-------------------------------------------------------------------------------------------------------------------
            int syspchoice;// Variable for defining the Type of System Queue
            cout<<"\n\nEnter the scheduling algorithm to be applied on System Process Queue\n";
            cout<<"1: Priority Scheduling\n2: Shortest Job First\n";
            cin>>syspchoice;

            while(syspchoice!=1 && syspchoice!=2)
            {
                cout<<"Invalid Choice, Enter Valid Choice: ";
                cin>>syspchoice;

            }
            int l=0;

            if(syspchoice==2)                                                     // =Shortest Job First for System Queue
            {
                for(i=0; i<j; i++)
                {
                    pos=i;
                    for(l=i+1; l<j; l++)
                    {
                        if(sysq[l][0]<sysq[pos][0])
                            pos=l;
                    }

                    temp=sysq[i][1];
                    sysq[i][1]=sysq[pos][1];
                    sysq[pos][1]=temp;

                    temp=sysq[i][0];
                    sysq[i][0]=sysq[pos][0];
                    sysq[pos][0]=temp;

                }

                wt[0]=0;

                for(i=1; i<j; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=sysq[l][1];

                    total+=wt[i];
                }

                avg_wt=total/n;
                total=0;
                cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
                for(i=0; i<j; i++)
                {
                    tat[i]=sysq[i][1]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<sysq[i][1]<<"]\t\t  "<<sysq[i][0]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;



            cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<j; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<sysq[i][1];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<j; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];

            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<j; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<j; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {

                    cout<<alloc[i][l]<<" ";

                }

            }
            for(i=0; i<j; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<j; i++)
            {
                for(l=0; l<3; l++)
                {
                    need[i][l]=maxall[i][l]-alloc[i][l];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<j; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {
                    cout<<need[i][l]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<j)
            {
                iter++;
                if(iter==(4*j)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or safe sequence is not possible";
                    break;
                }

                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<j; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(sysq[i][1]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }
                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=sysq[i][1];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;

                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<j; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<j; i++)
            {
                cout<<" "<<safeseq[i];
            }

            int vemp, xemp;
            int i=0;
            for(i=0; i<j; i++)
            {
                vemp=sysq[(arraypos[i])][1];// =p(1)=2;
                xemp=sysq[i][1];//=1
                sysq[i][1]=vemp;//=> 1=2;
                sysq[(arraypos[i])][1]=xemp;//=>2=1;


                vemp=sysq[(arraypos[i])][0];// =p(1)=2;
                xemp=sysq[i][0];//=1
                sysq[i][0]=vemp;//=> 1=2;
                sysq[(arraypos[i])][0]=xemp;//=>2=1;

                vemp=arraypos[i];//=1
                int l=0;
                for(l=0; l<j; l++)
                {
                    if(arraypos[l]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[l];//=0
                arraypos[l]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;

                for(i=1; i<j; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=sysq[l][1];

                    total+=wt[i];
                }

                avg_wt=total/n;
                total=0;
                cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
                for(i=0; i<j; i++)
                {
                    tat[i]=sysq[i][1]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<sysq[i][1]<<"]\t\t  "<<sysq[i][0]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;


            }

//EOS for SJF for System Queue-----------------------------------------------------------------------------------------------------------------------------------------

            else if(syspchoice==1)                                          // =Priority Scheduling for System Queue
            {
                int syspriority[20];                                       //=Array for storing Priority of System Queue

                for(i=0; i<j; i++)                                          //loop for taking in the Priority of System Process
                {

                    cout<<"\nEnter Priority for P["<<sysq[i][1]<<"]\n";
                    cin>>syspriority[i];

                }


                for(i=0; i<j; i++)              //Selection Sort on Priority
                {
                    pos=i;
                    for(l=i+1; l<j; l++)
                    {
                        if(syspriority[l]<syspriority[pos])
                            pos=l;
                    }

                    temp=syspriority[i];
                    syspriority[i]=syspriority[pos];
                    syspriority[pos]=temp;


                    temp=sysq[i][1];
                    sysq[i][1]=sysq[pos][1];
                    sysq[pos][1]=temp;

                    temp=sysq[i][0];
                    sysq[i][0]=sysq[pos][0];
                    sysq[pos][0]=temp;

                }

                wt[0]=0;


                for(i=1; i<j; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=sysq[l][0];

                    total+=wt[i];
                }

                avg_wt=total/n;

                total=0;

                cout<<"\nProcess\t    Burst Time\t      Priority\t    Waiting Time\t    Turnaround Time";
                for(i=0; i<j; i++)
                {
                    tat[i]=sysq[i][0]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<sysq[i][1]<<"]\t\t  "<<sysq[i][0]<<"\t\t    "<<syspriority[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;











                cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<j; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<sysq[i][1];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<j; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];

            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<j; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<j; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {

                    cout<<alloc[i][l]<<" ";

                }

            }
            for(i=0; i<j; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<j; i++)
            {
                for(l=0; l<3; l++)
                {
                    need[i][l]=maxall[i][l]-alloc[i][l];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<j; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {
                    cout<<need[i][l]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<j)
            {
                iter++;
                if(iter==(4*j)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or safe sequence is not possible";
                    break;
                }

                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<j; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(sysq[i][1]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }

                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=sysq[i][1];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;



                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<j; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<j; i++)
            {
                cout<<" "<<safeseq[i];
            }



            int vemp, xemp;
            int i=0;
            for(i=0; i<j; i++)
            {
                vemp=sysq[(arraypos[i])][1];// =p(1)=2;
                xemp=sysq[i][1];//=1
                sysq[i][1]=vemp;//=> 1=2;
                sysq[(arraypos[i])][1]=xemp;//=>2=1;


                vemp=sysq[(arraypos[i])][0];// =p(1)=2;
                xemp=sysq[i][0];//=1
                sysq[i][0]=vemp;//=> 1=2;
                sysq[(arraypos[i])][0]=xemp;//=>2=1;

                vemp=syspriority[(arraypos[i])];
                xemp=syspriority[i];
                syspriority[i]=vemp;
                syspriority[(arraypos[i])]=xemp;

                vemp=arraypos[i];//=1
                int l=0;
                for(l=0; l<j; l++)
                {
                    if(arraypos[l]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[l];//=0
                arraypos[l]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;


                for(i=1; i<j; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=sysq[l][0];

                    total+=wt[i];
                }

                avg_wt=total/n;

                total=0;

                cout<<"\nProcess\t    Burst Time\t      Priority\t    Waiting Time\t    Turnaround Time";
                for(i=0; i<j; i++)
                {
                    tat[i]=sysq[i][0]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<sysq[i][1]<<"]\t\t  "<<sysq[i][0]<<"\t\t    "<<syspriority[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;



//EOS for System Priority Process Queue--------------------------------------------------------------------------------------------------------------------

            }
//EOS for System Process Queue--------------------------------------------------------------------------------------------------------------------

            int usrchoice;                 // Variable for defining the Type of User Queue
            cout<<"\n\nEnter the scheduling algorithm to be applied on User Process Queue\n";
            cout<<"1: Priority Scheduling\n2: Shortest Job First\n";
            cin>>usrchoice;
            l=0;



            if(usrchoice==2)                                                     // =Shortest Job First for User Queue
            {
                for(i=0; i<k; i++)
                {
                    pos=i;
                    for(l=i+1; l<k; l++)
                    {
                        if(usq[l][0]<usq[pos][0])
                            pos=l;
                    }

                    temp=usq[i][1];
                    usq[i][1]=usq[pos][1];
                    usq[pos][1]=temp;

                    temp=usq[i][0];
                    usq[i][0]=usq[pos][0];
                    usq[pos][0]=temp;

                }

                wt[0]=0;

                for(i=1; i<k; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=usq[l][1];

                    total+=wt[i];
                }

                avg_wt=total/n;

                total=0;

                cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
                for(i=0; i<k; i++)
                {
                    tat[i]=usq[i][1]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<usq[i][1]<<"]\t\t  "<<usq[i][0]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;







            cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<k; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<usq[i][1];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<k; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];

            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<k; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<k; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {

                    cout<<alloc[i][l]<<" ";

                }

            }
            for(i=0; i<k; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<k; i++)
            {
                for(l=0; l<3; l++)
                {
                    need[i][l]=maxall[i][l]-alloc[i][l];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<k; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {
                    cout<<need[i][l]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<k)
            {
                iter++;
                if(iter==(4*k)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or safe sequence is not possible";
                    break;
                }

                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<k; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(usq[i][1]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }

                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=usq[i][1];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;



                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<k; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<k; i++)
            {
                cout<<" "<<safeseq[i];
            }



            int vemp, xemp;
            int i=0;
            for(i=0; i<k; i++)
            {
                vemp=usq[(arraypos[i])][1];// =p(1)=2;
                xemp=usq[i][1];//=1
                usq[i][1]=vemp;//=> 1=2;
                usq[(arraypos[i])][1]=xemp;//=>2=1;


                vemp=usq[(arraypos[i])][0];// =p(1)=2;
                xemp=usq[i][0];//=1
                usq[i][0]=vemp;//=> 1=2;
                usq[(arraypos[i])][0]=xemp;//=>2=1;

                vemp=arraypos[i];//=1
                int l=0;
                for(l=0; l<k; l++)
                {
                    if(arraypos[l]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[l];//=0
                arraypos[l]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;

                for(i=1; i<k; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=usq[l][1];

                    total+=wt[i];
                }

                avg_wt=total/n;
                total=0;
                cout<<"\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time";
                for(i=0; i<k; i++)
                {
                    tat[i]=usq[i][1]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<usq[i][1]<<"]\t\t  "<<usq[i][0]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;




            }
//EOS for User SJF Process Queue-------------------------------------------------------------------------------------------------------------------------------

            else if(usrchoice==1)                                          // = Priority Scheduling for User Queue
            {
                l=0;
                int usrpriority[20];                                       //=Array for storing Priority of User Queue

                for(i=0; i<k; i++)                                          //loop for taking in the Priority of System Process
                {

                    cout<<"\nEnter Priority for P["<<usq[i][1]<<"]\n";
                    cin>>usrpriority[i];

                }

                for(i=0; i<k; i++)              //Selection Sort on Priority
                {
                    pos=i;
                    for(l=i+1; l<k; l++)
                    {
                        if(usrpriority[l]<usrpriority[pos])
                            pos=l;
                    }
                    temp=usrpriority[i];
                    usrpriority[i]=usrpriority[pos];
                    usrpriority[pos]=temp;
                    temp=usq[i][1];
                    usq[i][1]=usq[pos][1];
                    usq[pos][1]=temp;

                    temp=usq[i][0];
                    usq[i][0]=usq[pos][0];
                    usq[pos][0]=temp;

                }

                wt[0]=0;


                for(i=1; i<k; i++)
                {
                    wt[i]=0;
                    for(l=0; l<i; l++)
                        wt[i]+=usq[l][0];

                    total+=wt[i];
                }

                avg_wt=total/n;

                total=0;

                cout<<"\nProcess\t    Burst Time\t      Priority\t    Waiting Time\t    Turnaround Time";
                for(i=0; i<k; i++)
                {
                    tat[i]=usq[i][0]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<usq[i][1]<<"]\t\t  "<<usq[i][0]<<"\t\t    "<<usrpriority[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;




                cout<<"\n\nNow applying Bankers Algorithm\n";
            int availres[3];
            int maxall[20][3];
            int alloc[20][3];


            for(i=0; i<k; i++)
            {

                cout<<"\n The "<<i+1<<" Processes is "<<usq[i][1];
            }

            for(i=0; i<3; i++)
            {
                cout<<"\nEnter the max available instance of Resource #"<<i+1<<": ";
                cin>>availres[i];
            }
            cout<<"\n                                                          ";
            cout<<"R1 R2 R3";
            for(i=0; i<k; i++)
            {

                cout<<"\nEnter the max allocation of each resource for Process #"<<i+1<<": ";
                cin>>maxall[i][0];
                cin>>maxall[i][1];
                cin>>maxall[i][2];



            }
            cout<<"\n                                                         ";
            cout<<"R1  R2  R3";
            for(i=0; i<k; i++)
            {
                cout<<"\nEnter the current allocation of resource for Process #"<<i+1<<": ";
                cin>>alloc[i][0];
                cin>>alloc[i][1];
                cin>>alloc[i][2];
            }
            int x=availres[0], y=availres[1], z=availres[2];


            cout<<"\nPrinting allocation matrix";

            for(i=0; i<k; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {

                    cout<<alloc[i][l]<<" ";

                }

            }
            for(i=0; i<k; i++)
            {
                x=x-alloc[i][0];
                y=y-alloc[i][1];
                z=z-alloc[i][2];
            }

            cout<<"\n\nThe available are "<<x<<" "<<y<<" "<<z;
            int need[20][3];
            for(i=0; i<k; i++)
            {
                for(l=0; l<3; l++)
                {
                    need[i][l]=maxall[i][l]-alloc[i][l];

                }

            }

            cout<<"\nPrinting need matrix";
            for(i=0; i<k; i++)
            {
                cout<<"\n";
                for(l=0; l<3; l++)
                {
                    cout<<need[i][l]<<" ";
                }
            }

            int safeseq[20];
            int ssv=0;    // safe sequence variable
            int flag=0;
            int flag2=0;
            int inner;
            int inner2;
            int arraypos[20];
            int iter=0;

            while(ssv<k)
            {
                iter++;
                if(iter==(4*k)){

                    cout<<"\n\n\n\n\n\nSolution not possible!! The likely cause is entering incorrect values or safe sequence is not possible";
                    break;
                }

                //cout<<"\n\n\n\n\n\nIteration number #"<<ssv;

                for(i=0; i<k; i++)
                {

                    cout<<"\n\n\nFor Process P["<<i<<"]";
                    // for(inner=0;inner<n;inner++){
                    for(inner2=0; inner2<ssv; inner2++)
                    {

                        if(usq[i][1]==safeseq[inner2])
                        {
                            flag2=1;
                        }

                    }

                    //}
                    cout<<"\nPrinting Flag 2:"<<flag2;
                    if(flag2==0)
                    {
                        flag2=0;
                        cout<<"\nThe values of need matrix and available array is:";
                        cout<<" "<<need[i][0]<<x;
                        cout<<" "<<need[i][1]<<y;
                        cout<<" "<<need[i][2]<<z;


                        if(need[i][0]>x || need[i][1]>y || need[i][2]>z)
                        {
                            flag=1;
                        }

                        cout<<"\nPrinting Flag 1:"<<flag;
                        if(flag==0)
                        {

                            cout<<"\nPrevious Values of x y z: "<<x<<" "<<y<<" "<<z;
                            cout<<"\nValue to be added: "<<alloc[i][0]<<" "<<alloc[i][1]<<" "<<alloc[i][2];
                            flag=0;
                            x+=alloc[i][0];
                            y+=alloc[i][1];
                            z+=alloc[i][2];
                            cout<<"\nNew Values of x y z: "<<x<<" "<<y<<" "<<z;

                            //cout<<"\nValue to be added in arraypos[ssv]: "<<i;
                            arraypos[ssv]=i;
                            //cout<<"\nValue to be added in safeseq[ssv]: "<<p[i];
                            safeseq[ssv]=usq[i][1];
                            ssv+=1;
                            //cout<<"\nThe new value of ssv is: "<<ssv;



                        }
                        else
                        {
                            flag=0;
                            continue;
                        }


                    }
                    else
                    {
                        flag2=0;
                        continue;
                    }
                }

            }
            cout<<"\nThe arraypos sequence is:";
            for(i=0; i<k; i++)
            {
                cout<<" "<<arraypos[i];
            }
            cout<<"\nThe safe sequence is:";
            for(i=0; i<k; i++)
            {
                cout<<" "<<safeseq[i];
            }

            int vemp, xemp;
            int i=0;
            for(i=0; i<k; i++)
            {
                vemp=usq[(arraypos[i])][1];// =p(1)=2;
                xemp=usq[i][1];//=1
                usq[i][1]=vemp;//=> 1=2;
                usq[(arraypos[i])][1]=xemp;//=>2=1;


                vemp=usq[(arraypos[i])][0];// =p(1)=2;
                xemp=usq[i][0];//=1
                usq[i][0]=vemp;//=> 1=2;
                usq[(arraypos[i])][0]=xemp;//=>2=1;


                vemp=usrpriority[(arraypos[i])];
                xemp=usrpriority[i];
                usrpriority[i]=vemp;
                usrpriority[(arraypos[i])]=xemp;

                vemp=arraypos[i];//=1
                int l=0;
                for(l=0; l<k; l++)
                {
                    if(arraypos[l]==i)
                    {
                        break;
                    }
                }
                xemp=arraypos[l];//=0
                arraypos[l]=vemp;//0 is replaced by 1;
                arraypos[i]=xemp;//1 is replaced by 0;
            }

            total=0;

            wt[0]=0;


                for(i=1; i<k; i++)
                {
                    wt[i]=0;
                    for(l=0; l<k; l++)

                        wt[i]+=usq[l][0];

                    total+=wt[i];
                }

                avg_wt=total/n;

                total=0;

                cout<<"\nProcess\t    Burst Time\t      Priority\t    Waiting Time\t    Turnaround Time";
                for(i=0; i<k; i++)
                {
                    tat[i]=usq[i][0]+wt[i];
                    total+=tat[i];
                    cout<<"\nP["<<usq[i][1]<<"]\t\t  "<<usq[i][0]<<"\t\t    "<<usrpriority[i]<<"\t\t    "<<wt[i]<<"\t\t\t"<<tat[i];
                }

                avg_tat=total/n;
                cout<<"\n\nAverage Waiting Time="<<avg_wt;
                cout<<"\nAverage Turnaround Time="<<avg_tat;



//EOS for User Priority Process Queue-------------------------------------------------------------------------------------------------------------------------------

            }

//EOS for User Process Queue-------------------------------------------------------------------------------------------------------------------------------

        }

        cout<<"\n\nDo You Want to Run Again?\nEnter 1 for Yes\nEnter 2 for No\n";
        cin>>rc;

        if(rc==2)
        {
            break;
        }
    }
    return 0;
}





