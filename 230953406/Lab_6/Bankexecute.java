import java.util.Scanner;
class Bank
{
    int r;
    double bal,si;
    int t;
    void getRateOfInterest()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter balance: ");
        bal=sc.nextDouble();
        System.out.println("Enter time: ");
        t=sc.nextInt();
        System.out.println("Enter rate of interest: ");
        r=sc.nextInt();
        si=(bal*r*t)/100;
        bal=bal+si;
        System.out.println("The balance after interest is: "+bal);
    }
}
class SBI extends Bank
{
    int r=8;
    void getRateOfInterest()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter balance: ");
        bal=sc.nextDouble();
        System.out.println("Enter time: ");
        t=sc.nextInt();
        si=(bal*r*t)/100;
        bal=bal+si;
        System.out.println("The balance after interest is: "+bal);
    }
}
class ICICI extends Bank
{
    int r=7;
    void getRateOfInterest()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter balance: ");
        bal=sc.nextDouble();
        System.out.println("Enter time: ");
        t=sc.nextInt();
        si=(bal*r*t)/100;
        bal=bal+si;
        System.out.println("The balance after interest is: "+bal);
    }
}
class AXIS extends Bank
{
    int r=9;
    void getRateOfInterest()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter balance: ");
        bal=sc.nextDouble();
        System.out.println("Enter time: ");
        t=sc.nextInt();
        si=(bal*r*t)/100;
        bal=bal+si;
        System.out.println("The balance after interest is: "+bal);
    }
}
public class Bankexecute 
{
    public static void main(String args[])
    {
        Scanner sc=new Scanner(System.in);
        Bank a=new Bank();
        SBI s=new SBI();
        ICICI i=new ICICI();
        AXIS ax=new AXIS();
        Bank r;
        int option;
        do
        {
          System.out.println("\nEnter\n1.SBI\n2.ICICI\n3.AXIS\n4.Exit\n");
          option=sc.nextInt();
          switch(option)
          {
            case 1:
            r=s;
            r.getRateOfInterest();
            break;
            case 2:
            r=i;
            r.getRateOfInterest();
            break;
            case 3:
            r=ax;
            r.getRateOfInterest();
            break;
            case 4:
            break;
          }
        }while(option!=4);
    }
}
