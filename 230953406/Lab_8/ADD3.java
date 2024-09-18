interface Sports {
    int getNumberOfGoals();
    void dispTeam();
}
class Hockey implements Sports {
    int goals;
    String team;
    Hockey(int goals, String team) {
        this.goals = goals;
        this.team = team;
    }
    public int getNumberOfGoals() {
        return goals;
    }
    public void dispTeam() {
        System.out.println("Hockey Team: " + team + " | Goals: " + goals);
    }
}
class Football implements Sports {
    int goals;
    String team;
    Football(int goals, String team) {
        this.goals = goals;
        this.team = team;
    }
    public int getNumberOfGoals() {
        return goals;
    }
    public void dispTeam() {
        System.out.println("Football Team: " + team + " | Goals: " + goals);
    }
}

class SportsResult{
    public static void main(String[] args) {
        Hockey teamA = new Hockey(3, "China");
        Hockey teamB = new Hockey(5, "India");
        Football TeamA = new Football(2, "Barcelona");
        Football TeamB = new Football(1, "Real Madrid");
        teamA.dispTeam();
        teamB.dispTeam();
        TeamA.dispTeam();
        TeamB.dispTeam();
        if (teamA.getNumberOfGoals() > teamB.getNumberOfGoals()) {
            System.out.println("Winning Team: China (Hockey)");
        }
        else {
            System.out.println("Winning Team: India (Hockey)");
        }
        if (TeamA.getNumberOfGoals() > TeamB.getNumberOfGoals()) {
            System.out.println("Winning Team: Barcelona (Football)");
        }
        else {
            System.out.println("Winning Team: Real Madrid (Football)");
        }
    }
}
