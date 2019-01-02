import java.io.*
import java.util.StringTokenizer


class ProblemB {
    lateinit var input: FastScanner
    lateinit var output: PrintWriter

    lateinit var parents: Array<Int>
    lateinit var ranges: Array<Int>

    val edgeIndex = hashMapOf<Edge, Int>()

    fun solve() {
        val n = input.nextInt()
        val m = input.nextInt()
        val s = input.nextLong()

        val listOfEdges = read(m)
        val tree = hashSetOf<Edge>()

        measureTime("kruskal_sort") {
            listOfEdges.sortBy { it.cost }
        }
        measureTime("kruskal") {
            parents = Array(n + 1) { it }
            ranges = Array(n + 1) { 0 }

            for (i in m - 1 downTo 0) {
                val (a, b, _) = listOfEdges[i]
                if (getDsu(a) != getDsu(b)) {
                    tree.add(listOfEdges[i])
                    unite(a, b)
                }
            }
        }

        val canDelete = mutableListOf<Edge>()
        measureTime("rebra kotorye ne voshli v derevo") {
            for (edge in listOfEdges) {
                if (!tree.contains(edge)) {
                    canDelete.add(edge)
                }
            }
        }

        measureTime("^ sort") {
            canDelete.sortBy { it.cost }
        }


        var curSum = 0L
        val answer = mutableListOf<Int>()

        measureTime("nabirayem") {
            for (edge in canDelete) {
                val newSum = curSum + edge.cost
                if (newSum > s || newSum < 0L) {
                    break
                } else {
                    answer.add(edgeIndex[edge]!!)
                    curSum = newSum
                }
            }
        }
        measureTime("pishem") {
            output.write("${answer.size}\n" + answer.joinToString(" "))
        }
    }

    fun getDsu(vertex: Int): Int {
        if (parents[vertex] != vertex) {
            parents[vertex] = getDsu(parents[vertex])
        }
        return parents[vertex]
    }

    fun unite(first: Int, second: Int) {
        val a = getDsu(first)
        val b = getDsu(second)
        if (a != b) {
            if (ranges[a] == ranges[b])
                ++ranges[a]
            if (ranges[a] > ranges[b]) {
                parents[b] = a
            } else {
                parents[a] = b
            }
        }
    }

    fun read(n: Int): MutableList<Edge> {
        val list = mutableListOf<Edge>()
        for (i in 0 until n) {
            val tmp = Edge(input.nextInt(), input.nextInt(), input.nextLong())
            list.add(tmp)
            edgeIndex[tmp] = i + 1
        }
        return list
    }

    fun run() {
        input = FastScanner(File("destroy.in"))
        output = PrintWriter(File("destroy.out"))
        output.use {
            solve()
        }
    }

    fun measureTime(name: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println("$name: run for ${(System.nanoTime() - start)/10e9}")
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

    data class Edge(val first: Int, val second: Int, val cost: Long)


}

fun main(args: Array<String>) {
    ProblemB().run()
}