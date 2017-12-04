package zeus;

import javafx.application.Application;
import javafx.geometry.Rectangle2D;
import javafx.scene.Group;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.ScrollPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.Rectangle;
import javafx.stage.Screen;
import javafx.stage.Stage;

/**
 * Main function.
 * The entry point of the program, as well as handles the simulation events.
 * @author Czar Ian Echavez
 *
 */
public class Main extends Application{

	//Global variables
	
	//window size
	int winX, winY;
	
	//toggle for running sim
	boolean runSim = false;
	
	/**extry point of program
	 * all this does is launch the application through JavaFX
	 * @param args
	 */
	public static void main(String[] args) {
	    launch(args);
	  }
	
	@Override
	public void start(Stage stage) throws Exception {

		//get window size
		Rectangle2D screenRect = Screen.getPrimary().getVisualBounds();
		winX = (int) screenRect.getMinX();
		winY = (int) screenRect.getMinY();
		
		Group root = new Group();
	    Scene scene = new Scene(root, winX, winY);
	    stage.setScene(scene);

	    Group g = new Group();

	    Polygon polygon = new Polygon();
	    polygon.getPoints().addAll(new Double[]{
	        0.0, 0.0,
	        20.0, 10.0,
	        10.0, 20.0 });
	    
	    g.getChildren().add(polygon);
	    
	    scene.setRoot(g);
	    stage.setMaximized(true);
	    stage.show();
	}

}
