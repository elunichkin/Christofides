import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;

public class GraphPanel extends JPanel {
    private int maxCoord;
    private ArrayList<Vertex> vertices;
    private HashMap<Edge, Color> edges;
    private int start, finish;

    public GraphPanel(Graph G, int mc) {
        this.setOpaque(true);
        this.maxCoord = mc;
        this.vertices = G.getVertices();
        this.edges = new HashMap<>();
        this.start = G.getStart();
        this.finish = G.getFinish();
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
        int size;
        for (Vertex v : vertices) {
            if (v.ind == start) {
                g2d.setPaint(Color.green);
                size = 3;
            } else if (v.ind == finish) {
                g2d.setPaint(Color.red);
                size = 3;
            } else {
                g2d.setPaint(Color.black);
                size = 2;
            }
            g2d.fillOval((int)((v.x + (double)maxCoord) / stepX) - size, (int)(((double)maxCoord - v.y) / stepY) - size,
                    2 * size, 2 * size);
        }

        //Edges:
        for (HashMap.Entry<Edge, Color> entry : edges.entrySet()) {
            g2d.setPaint(entry.getValue());
            Edge e = entry.getKey();
            g2d.drawLine((int)((e.u.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.u.y) / stepY),
                    (int)((e.v.x + (double)maxCoord) / stepX), (int)(((double)maxCoord - e.v.y) / stepY));
        }
    }

    public void addEdge(Edge edge, Color color, boolean replace) {
        if (replace) {
            removeEdge(edge);
        }
        edges.put(edge, color);
        repaint();
        try {
            Thread.sleep(200);
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    public void drawPath(ArrayList<Vertex> vs, Color color) {
        for (int i = 0; i < vs.size() - 1; ++i) {
            addEdge(new Edge(vs.get(i), vs.get(i + 1)), color, true);
        }
    }

    public void finalize(ArrayList<Vertex> vs) {
        edges.clear();
        for (int i = 0; i < vs.size() - 1; ++i) {
            edges.put(new Edge(vs.get(i), vs.get(i + 1)), Color.black);
        }
        repaint();
    }

    private void removeEdge(Edge edge) {
        ArrayList<Edge> toRemove = new ArrayList<>();
        for (Edge e : edges.keySet()) {
            if (e.u.ind == edge.u.ind && e.v.ind == edge.v.ind) {
                toRemove.add(e);
            }
            if (e.u.ind == edge.v.ind && e.v.ind == edge.u.ind) {
                toRemove.add(e);
            }
        }
        for (Edge e : toRemove) {
            edges.remove(e);
        }
    }
}
