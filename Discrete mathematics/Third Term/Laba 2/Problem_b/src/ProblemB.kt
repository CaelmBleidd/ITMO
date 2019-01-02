import java.io.StreamTokenizer
import java.lang.Math.*
import java.util.*
import kotlin.Comparator
import kotlin.collections.HashMap

class ProblemB {
    lateinit var reader: StreamTokenizer
    private val EPS = 1e-9

    private fun solve() {

        val n = nextInt()
        val lines = readLines(n)

        val graph = HashMap<Point, ArrayList<Point>>()
        var mapCounter = 0
        val mapPoint = HashMap<Point, Int>()
        val mapIndex = HashMap<Int, Point>()

        fun id(p: Point): Int = mapPoint.getOrPut(p) {
            val index = mapCounter++
            mapIndex[index] = p
            index
        }


        for (i in 0 until n) {
            val iss = ArrayList<Point>()

            for (j in 0 until n) {
                if (i == j || lines[i].start == lines[i].second || lines[j].start == lines[j].second)
                    continue

                intersect(lines[i], lines[j])?.let { iss.add(it) }
            }

            iss.sort()

            for (j in 0..iss.size - 2) if (iss[j] != iss[j + 1]) {
                graph.getOrPut(iss[j]) { ArrayList() }.add(iss[j + 1])
                graph.getOrPut(iss[j + 1]) { ArrayList() }.add(iss[j])
            }
        }

        for ((p, list) in graph) graph[p] = arrayListOf(*list.distinct().toTypedArray())
        for ((p, list) in graph) list.sortWith(Comparator { first, second ->
            when {
                p.angleTo(first) < p.angleTo(second) -> return@Comparator -1
                p.angleTo(first) > p.angleTo(second) -> return@Comparator 1
                else -> return@Comparator 0
            }
        })

        val indexed = Array(graph.size) { ArrayList<Int>() }
        for ((p, list) in graph) {
            for (i in list) {
                indexed[id(p)].add(id(i))
            }
        }

        val used = Array(indexed.size) { Array(indexed[it].size) { false } }
        val areas = ArrayList<Double>()

        for (i in 0 until indexed.size) {
            for (j in 0 until indexed[i].size) {
                if (used[i][j]) continue
                used[i][j] = true

                var next = i
                var cur = indexed[i][j]
                val facet = ArrayList<Int>()
                var area = 0.0

                while (true) {
                    facet.add(cur)
                    area += mapIndex[next]!!.x * mapIndex[cur]!!.y - mapIndex[next]!!.y * mapIndex[cur]!!.x
                    var index = indexed[cur].indexOf(next)
                    if (++index == indexed[cur].size)
                        index = 0
                    if (used[cur][index]) break
                    used[cur][index] = true
                    next = cur
                    cur = indexed[cur][index]
                }

                area /= 2

                if (area < 0 && abs(area) >= EPS) areas.add(abs(area))
            }
        }

        areas.sort()
        println(areas.size)
        areas.forEach {
            println(it)
        }
    }

    fun run() {
        reader = StreamTokenizer(System.`in`.bufferedReader())
        solve()
    }

    private fun nextInt(): Int {
        reader.nextToken()
        return reader.nval.toInt()
    }

    private fun nextDouble(): Double {
        reader.nextToken()
        return reader.nval
    }

    data class Point(val x: Double, val y: Double) : Comparable<Point> {
        fun angleTo(other: Point): Double {
            val theta = toDegrees(atan2(other.y - y, other.x - x))
            return if (theta < 0) theta + 360 else theta
        }

        override fun compareTo(other: Point): Int {
            return if (abs(other.x - x) < 1e-9 && abs(other.y - y) < 1e-9) 0
            else if (x < other.x - 1e-9 || abs(x - other.x) < 1e-9 && y < other.y - 1e-9) -1
            else 1
        }

        override fun equals(other: Any?): Boolean {
            if (other is Point) {
                return other.x == x && other.y == y
            }
            return false
        }

        override fun hashCode(): Int = x.hashCode() + y.hashCode()
    }

    private fun readLines(n: Int): ArrayList<Line> {
        val array = arrayListOf<Line>()
        for (i in 0 until n)
            array.add(
                Line(
                    Point(nextDouble() + 101, nextDouble() + 101),
                    Point(nextDouble() + 101, nextDouble() + 101)
                )
            )
        return array
    }

    private fun intersect(first: Line, second: Line): Point? {
        val x1 = first.start.x
        val x2 = first.second.x
        val x3 = second.start.x
        val x4 = second.second.x

        val y1 = first.start.y
        val y2 = first.second.y
        val y3 = second.start.y
        val y4 = second.second.y

        val denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

        if (abs(denominator) < EPS)
            return null

        return Point(
            ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denominator,
            ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denominator
        )
    }

    data class Line(val start: Point, val second: Point)


}


fun main(args: Array<String>) {
    ProblemB().run()
}