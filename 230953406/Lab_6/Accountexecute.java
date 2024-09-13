import java.util.Scanner;

class account {
    String name;
    int accno;
    String type;
    double bal;

    account() {
        bal = 0;
    }

    void getdata() {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter name");
        name = sc.next();
        System.out.println("Enter the type of account");
        type = sc.next();
    }

    void display() {
        System.out.println("Name = " + name);
        System.out.println("Account number = " + (accno+1));
        System.out.println("Account type = " + type);
        System.out.println("Balance = " + bal);
    }

    void deposit() {
        int n;
        System.out.println("Enter the amount to deposit");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        bal += n;
        display();
    }

}

class savings extends account {
    void interest() {
        Scanner sc = new Scanner(System.in);
        int t, r;
        System.out.println("Enter time and rate of interest");
        t = sc.nextInt();
        r = sc.nextInt();
        double si;
        si = (bal * t * r) / 100;
        bal = bal + si;
        display();

    }

    void withdraw() {
        int n;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the amount to be withdraw");
        n = sc.nextInt();
        if (n > bal)
            System.out.println("Insufficient balance");
        else
            bal = bal - n;
        display();
    }

}

class current extends account {
    int min = 500;

    void withdraw() {
        Scanner sc = new Scanner(System.in);
        int n;
        double pens = 0;
        System.out.println("Enter the amount to be withdrawn");
        n = sc.nextInt();
        bal = bal - n;
        if (bal < min) {
            pens = (bal * 1) / 100;
            bal = bal - pens;

        }
        display();
        System.out.println("Minimum balance reached");
        System.out.println("Penalty of " + pens + " deducted");

    }
}

class Accountexecute {
    public static void main(String args[]) {
        int n;
        account a = new account();

        Scanner sc = new Scanner(System.in);
        System.out.println("Enter 1 for savings account");
        System.out.println("Enter 2 for current account");
        n = sc.nextInt();
        switch (n) {
            case 1: {
                savings s = new savings();
                s.getdata();
                int j = 0;
                while (j != -1) {
                    System.out.println("Enter 1 to deposit");
                    System.out.println("Enter 2 to display");
                    System.out.println("Enter 3 to withdraw");
                    System.out.println("Enter 4 to compute interest");
                    System.out.println("Enter -1 to stp");
                    j = sc.nextInt();
                    switch (j) {
                        case 1: {
                            s.deposit();
                            break;
                        }
                        case 2: {
                            s.display();
                            break;
                        }
                        case 3: {
                            s.withdraw();
                            break;
                        }
                        case 4: {
                            s.interest();
                            break;
                        }
                    }
                }
                break;

            }

            case 2: {
                current c = new current();
                c.getdata();
                int j = 0;
                while (j != -1) {
                    System.out.println("Enter 1 to deposit");
                    System.out.println("Enter 2 to display");
                    System.out.println("Enter 3 to withdraw");
                    System.out.println("Enter -1 to stp");
                    j = sc.nextInt();
                    switch (j) {
                        case 1: {
                            c.deposit();
                            break;
                        }
                        case 2: {
                            c.display();
                            break;
                        }
                        case 3: {
                            c.withdraw();
                            break;
                        }
                    }
                }
                break;

            }
        }
    }
}