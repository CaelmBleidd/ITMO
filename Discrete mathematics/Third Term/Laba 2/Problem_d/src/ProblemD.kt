import java.io.BufferedReader
import java.io.FileReader
import java.io.PrintWriter
import java.util.*

class ProblemD {

    private val br = BufferedReader(FileReader("planaritycheck.in"))
    private var st: StringTokenizer? = null
    private val writer = PrintWriter("planaritycheck.out")

    fun run() {
        solve()
    }

    private fun solve() {
        val countAttempts = nextInt()
        val answer = mutableListOf<String>()

        for (i in 0 until countAttempts) {
            val graph = readGraph()
            if (graph.size < 5 || (graph.size == 5 && graph.countEdges != 10)) {
                answer.add("YES")
            } else if (graph.size == 5 && graph.countEdges == 10 || graph.size == 6 && graph.countEdges > 12) {
                answer.add("NO")
            } else {
                val newVertexes = mutableListOf<Int>()
                if (graph.endEdgesByStart[1] != null) newVertexes.add(1)
                if (graph.endEdgesByStart[2] != null) newVertexes.add(2)
                if (graph.endEdgesByStart[3] != null) newVertexes.add(3)
                if (graph.endEdgesByStart[4] != null) newVertexes.add(4)
                if (graph.endEdgesByStart[5] != null) newVertexes.add(5)
                if (graph.endEdgesByStart[6] != null) newVertexes.add(6)

                var isOk = true

                if (newVertexes.size > 5 && graph.countEdges >= 9 && hasK33(edges = graph.edges)) {
                    isOk = false
                }
                if (newVertexes.size > 5 && graph.countEdges >= 10 && hasK5(graph))
                    isOk = false
                if (newVertexes.size == 5 && graph.countEdges == 10)
                    isOk = false

                if (!isOk)
//                    answer.add("NO ${graph.line}")
                    answer.add("NO")
                else
//                    answer.add("YES ${graph.line}")
                    answer.add("YES")
            }
        }
        answer.forEach {
            writer.write("$it\n")
        }
        writer.close()
    }

    private fun hasK5(graph: Graph): Boolean {
        for (edge in graph.edges) {
            val (start, end) = edge
            val newEdges = mutableSetOf<Edge>()
            for (oneMoreEdge in graph.edges) {
                if (oneMoreEdge.end != end && oneMoreEdge.start != end) {
                    newEdges.add(oneMoreEdge)
                }
            }
            for (vertex in graph.endEdgesByStart[end]!!) {
                if (vertex != start)
                    newEdges.add(Edge(start, vertex))
            }
            if (isk5(newEdges))
                return true
        }
        for (edge in graph.edges) {
            val (start, end) = edge
            val newEdges = mutableSetOf<Edge>()
            for (oneMoreEdge in graph.edges) {
                if (oneMoreEdge.end != start && oneMoreEdge.start != start) {
                    newEdges.add(oneMoreEdge)
                }
            }
            for (vertex in graph.endEdgesByStart[start]!!) {
                if (vertex != end)
                    newEdges.add(Edge(end, vertex))
            }
            if (isk5(newEdges))
                return true
        }
        return false
    }

    private fun isk5(edges: MutableSet<Edge>): Boolean {
        if (edges.size != 10)
            return false
        else {
            var count = 0
            if (edges.contains(Edge(1, 2)) || edges.contains(Edge(2, 1)))
                count++
            if (edges.contains(Edge(1, 3)) || edges.contains(Edge(3, 1)))
                count++
            if (edges.contains(Edge(1, 4)) || edges.contains(Edge(4, 1)))
                count++
            if (edges.contains(Edge(1, 5)) || edges.contains(Edge(5, 1)))
                count++
            if (edges.contains(Edge(1, 6)) || edges.contains(Edge(6, 1)))
                count++
            if (edges.contains(Edge(3, 2)) || edges.contains(Edge(2, 3)))
                count++
            if (edges.contains(Edge(4, 2)) || edges.contains(Edge(2, 4)))
                count++
            if (edges.contains(Edge(5, 2)) || edges.contains(Edge(2, 5)))
                count++
            if (edges.contains(Edge(6, 2)) || edges.contains(Edge(2, 6)))
                count++
            if (edges.contains(Edge(3, 4)) || edges.contains(Edge(4, 3)))
                count++
            if (edges.contains(Edge(3, 5)) || edges.contains(Edge(5, 3)))
                count++
            if (edges.contains(Edge(3, 6)) || edges.contains(Edge(6, 3)))
                count++
            if (edges.contains(Edge(4, 5)) || edges.contains(Edge(5, 4)))
                count++
            if (edges.contains(Edge(4, 6)) || edges.contains(Edge(6, 4)))
                count++
            if (edges.contains(Edge(5, 6)) || edges.contains(Edge(6, 5)))
                count++
            return count == 10
        }
    }

    private fun hasK33(edges: MutableList<Edge>): Boolean {
        if (edges.size > 9) {
            for (edge in edges) {
                val newEdges = mutableListOf<Edge>()
                for (i in edges)
                    if (i != edge)
                        newEdges.add(i)
                if (hasK33(newEdges))
                    return true
            }
            return false
        } else {
            val part = MutableList(7) { -1 }
            val used = MutableList(7) { false }

            val graph = MutableList(7) {
                mutableListOf<Int>()
            }
            for (edge in edges) {
                graph[edge.end].add(edge.start)
                graph[edge.start].add(edge.end)
            }
            for (i in 1..6) {
                isBipartite(i, 1, graph, used, part)
            }
            return part[0] == -1
        }
    }

    private fun readGraph(): Graph {
        val line = next()
        val size = when (line.length) {
            0 -> 1
            1 -> 2
            3 -> 3
            6 -> 4
            10 -> 5
            15 -> 6
            else -> 0
        }

        var countEdges = 0
        val edges = mutableListOf<Edge>()
        val endEdgeByStart = mutableMapOf<Int, MutableList<Int>>()

        val graph = MutableList(size + 1) {
            MutableList(size + 1) {
                0
            }
        }
        var last = 0
        for (i in 1..size) {
            for (j in 1 until i) {
                if (line[last] == '1') {
                    countEdges++
                    edges.add(Edge(j, i))
                    if (endEdgeByStart[i] == null) {
                        endEdgeByStart[i] = mutableListOf(j)
                    } else {
                        endEdgeByStart[i]!!.add(j)
                    }
                    if (endEdgeByStart[j] == null)
                        endEdgeByStart[j] = mutableListOf(i)
                    else
                        endEdgeByStart[j]!!.add(i)
                }
                graph[i][j] = if (line[last++] == '1') 1 else 0
            }
        }
        return Graph(graph, size, countEdges, edges, endEdgeByStart, line)
    }


    private fun isBipartite(
        vertex: Int,
        lastColor: Int,
        graph: MutableList<MutableList<Int>>,
        used: MutableList<Boolean>,
        part: MutableList<Int>
    ) {

        if (part[0] != -1 || used[vertex]) return

        used[vertex] = true

        when (lastColor) {
            0 -> part[vertex] = 1
            1 -> part[vertex] = 0
            else -> part[vertex] = 0
        }

        for (i in graph[vertex]) {
            if (!used[i])
                isBipartite(i, part[vertex], graph, used, part)
            else {
                if (part[i] == part[vertex] && part[i] != -1)
                    part[0] = 10000
            }
        }

    }

    fun next(): String {
        val line = br.readLine()
        return if (line == null || line.isEmpty())
            ""
        else {
            st = StringTokenizer(line)
            st!!.nextToken()
        }
    }

    private fun nextInt(): Int {
        return next().toInt()
    }

    data class Edge(val start: Int, var end: Int)

    data class Graph(
        val graph: MutableList<MutableList<Int>>,
        val size: Int,
        val countEdges: Int,
        val edges: MutableList<Edge>,
        val endEdgesByStart: MutableMap<Int, MutableList<Int>>,
        val line: String
    )
}

fun main(args: Array<String>) {
    ProblemD().run()
}