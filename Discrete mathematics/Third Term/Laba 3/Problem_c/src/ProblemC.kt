import java.io.*
import java.util.StringTokenizer


class Problem_c {
    lateinit var reader: FastScanner
    lateinit var writer: PrintWriter


    fun solve() {
        val graph = readGraph()
        val mt = MutableList(graph.size + 1) { -1 }
        val used = MutableList(graph.size + 1) { false }


        for (i in 0 until graph.size) {
            val vertex = graph.vertices[i]
            used.replaceAll { false }
            kuhn(vertex.number, used, mt, graph)
        }

        for (i in 1..graph.size) {
            var result = 0
            for (j in mt.indices) {
                if (i == mt[j]) {
                    result = j
                    break
                }
            }
            writer.write("$result ")

        }
    }

    fun readGraph(): Graph {
        val size = reader.nextInt()
        val weights = mutableListOf<Long>()
        val edges = mutableListOf<MutableList<Int>>()
        val vertices = mutableListOf<Vertex>()

        weights.add(0)
        vertices.add(Vertex(0, 0L))
        edges.add(mutableListOf())

        for (i in 1..size) {
            weights.add(reader.nextLong())
            vertices.add(Vertex(i, weights[i]))
        }

        vertices.sortWith(Comparator { first, second ->
            when {
                first.weight < second.weight -> 1
                first.weight > second.weight -> -1
                else -> 0
            }
        })

        for (i in 1..size) {
            edges.add(mutableListOf())
            val amountOfVertices = reader.nextLong()
            for (j in 0 until amountOfVertices) {
                edges[i].add(reader.nextInt())
            }
        }

        return Graph(size, edges, weights, vertices)
    }

    fun kuhn(vertex: Int, used: MutableList<Boolean>, mt: MutableList<Int>, graph: Graph): Boolean {
        if (used[vertex]) {
            return false
        }
        used[vertex] = true
        for (i in 0 until graph.edges[vertex].size) {
            val to = graph.edges[vertex][i]
            if (mt[to] == -1 || kuhn(mt[to], used, mt, graph)) {
                mt[to] = vertex
                return true
            }
        }

        return false
    }

    fun run() {
        reader = FastScanner(File("matching" + ".in"))
        writer = PrintWriter(File("matching" + ".out"))

        solve()

        writer.close()
    }


    inner class FastScanner(file: File) {
        var br: BufferedReader = BufferedReader(FileReader(file))
        var st: StringTokenizer? = null

        fun next(): String {
            while (st == null || !st!!.hasMoreTokens()) {
                st = StringTokenizer(br.readLine())
            }
            return st!!.nextToken()
        }

        fun nextInt(): Int {
            return next().toInt()
        }

        fun nextLong(): Long {
            return next().toLong()
        }

        fun nextDouble(): Double {
            return next().toDouble()
        }

    }

    data class Graph(
        val size: Int,
        val edges: MutableList<MutableList<Int>>,
        val weights: MutableList<Long>,
        val vertices: MutableList<Vertex>
    )

    data class Vertex(val number: Int, val weight: Long)

    data class Edge(val first: Int, val second: Int, val weight: Long)
}

fun main(args: Array<String>) {
    Problem_c().run()
}