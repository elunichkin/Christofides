import java.util.ArrayList;
import java.util.Random;

public class RandomGraph {
    Random random;

    public RandomGraph() {
        random = new Random();
    }

    public ArrayList<Vertex> randomVertices(int maxSize, double maxCoord) {
        int n = random.nextInt(maxSize - 2) + 3;
        ArrayList<Vertex> vertices = new ArrayList<>();

        for (int i = 0; i < n; ++i) {
            double x = random.nextDouble() * (2 * maxCoord) - maxCoord;
            double y = random.nextDouble() * (2 * maxCoord) - maxCoord;
            vertices.add(new Vertex(x, y, i));
        }

        return vertices;
    }
}
