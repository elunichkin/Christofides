import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.Collections;

public class GraphPanel extends JPanel {
    private int maxCoord;
    private ArrayList<Vertex> vertices;
    private ArrayList<Edge> edges;
    private Color color;
    private int index;
    private int start, finish;

    public GraphPanel(int mc) {
        this.setOpaque(true);
        this.maxCoord = mc;
        this.color = Color.black;
    }

    @Override
    protected void paintComponent(Graphics g) {
        int w = getWidth();
        int h = getHeight();
        Graphics2D g2d = (Graphics2D)g;
        g2d.clearRect(0, 0, w, h);
        double stepX = 2.0 * maxCoord / w;
        double stepY = 2.0 * maxCoord / h;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        //Axis:
        g2d.setPaint(Color.darkGray);
        g2d.drawLine(0, (int)(maxCoord / stepY), w, (int)(maxCoord / stepY));
        g2d.drawLine((int)(maxCoord / stepX), 0, (int)(maxCoord / stepX), h);

        //Vertices:
        g2d.setPaint(Color.black);
        for (Vertex v : vertices) {
            if (v.ind == start) {
                g2d.setPaint(Color.green);
            } else if (v.ind == finish) {
                g2d.setPaint(Color.red);
            } else {
                g2d.setPaint(Color.black);
            }
            g2d.fillOval((int)((v.x + (double)maxCoord) / stepX) - 2, (int)(((double)maxCoord - v.y) / stepY) - 2, 4, 4);
        }

        //Edges:
        for (int i = 0; i < index; ++i) {
            Edge e = edges.get(i);
            g2d.drawLine((int)((e.u.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.u.y) / stepY),
                    (int)((e.v.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.v.y) / stepY));
        }
        g2d.setPaint(color);
        for (int i = index; i < edges.size(); ++i) {
            Edge e = edges.get(i);
            g2d.drawLine((int)((e.u.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.u.y) / stepY),
                    (int)((e.v.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.v.y) / stepY));
        }
    }

    public void changeGraph(Graph G, Color col, int ind) {
        vertices = G.getVertices();
        edges = G.getEdges();
        color = col;
        index = ind;
        start = G.getStart();
        finish = G.getFinish();
        repaint();
    }

    public void changeGraph(Graph G, Color col) {
        changeGraph(G, col, 0);
    }

    public void changeGraph(Graph G) {
        changeGraph(G, Color.black);
    }

    public void drawPath(Graph G, ArrayList<Vertex> path) {
        vertices = G.getVertices();
        color = Color.red;
        index = 0;

        edges = new ArrayList<>();
        for (int i = 0; i < path.size() - 1; ++i) {
            edges.add(new Edge(path.get(i), path.get(i + 1)));

            try {
                Thread.sleep(200);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }

            repaint();
        }
    }

    public void drawIntegerPath(Graph G, ArrayList<Integer> path) {
        ArrayList<Vertex> vertexPath = new ArrayList<>();
        for (int v : path) {
            vertexPath.add(G.getVertexByInd(v));
        }
        drawPath(G, vertexPath);
    }
}
