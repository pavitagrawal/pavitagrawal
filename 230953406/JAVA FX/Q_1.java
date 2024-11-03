import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.FlowPane;
import javafx.stage.Stage;
import javafx.scene.paint.Color;

public class FirstJavaFXApp extends Application {
    @Override
    public void start(Stage primaryStage) {
        Label label = new Label("Welcome to JavaFX programming");
        label.setTextFill(Color.MAGENTA);
        FlowPane flowPane = new FlowPane();
        flowPane.setHgap(10); // Set horizontal gap to desired value
        flowPane.setVgap(10); // Set vertical gap to desired value
        flowPane.getChildren().add(label);
        Scene scene = new Scene(flowPane, 500, 200);
        primaryStage.setTitle("This is the first JavaFX Application");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
