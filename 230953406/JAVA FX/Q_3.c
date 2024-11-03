import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class WelcomeWindow extends Application {
    @Override
    public void start(Stage primaryStage) {
        TextField username = new TextField();
        PasswordField password = new PasswordField();
        Label message = new Label();
        
        Button signIn = new Button("Sign in");
        signIn.setOnAction(e -> message.setText("Welcome " + username.getText()));
        
        GridPane grid = new GridPane();
        grid.setHgap(10); grid.setVgap(10);
        grid.add(new Label("User Name:"), 0, 0);
        grid.add(username, 1, 0);
        grid.add(new Label("Password:"), 0, 1);
        grid.add(password, 1, 1);
        grid.add(message, 0, 2, 2, 1);
        grid.add(signIn, 1, 3);
        
        primaryStage.setScene(new Scene(grid, 300, 150));
        primaryStage.setTitle("JavaFX Welcome");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
