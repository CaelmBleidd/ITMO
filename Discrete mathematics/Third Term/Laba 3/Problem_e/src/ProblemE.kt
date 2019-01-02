import java.io.BufferedReader
import java.io.File
import java.io.FileReader
import java.io.FileWriter
import java.util.*
import kotlin.collections.HashMap
import kotlin.collections.HashSet

class ProblemD {
    lateinit var reader: FastScanner
    lateinit var writer: FileWriter

    fun solve() {
        val (n, m, weights, need, list) = read()
        for (set in list) {
            var min = Long.MAX_VALUE
            var minNumber = 0
            for (element in set) {
                if (weights[element - 1] < min) {
                    min = weights[element - 1]
                    minNumber = element - 1
                }
            }
            need[minNumber] = false
        }
        var result = 0L
        for (i in need.indices) {
            if (need[i])
                result += weights[i]
        }

        writer.write(result.toString())
    }


    fun read(): Set {
        val n = reader.nextInt()
        val m = reader.nextInt()
        val weights = mutableListOf<Long>()
        val need = mutableListOf<Boolean>()
        val list = mutableListOf<TreeSet<Int>>()


        for (i in 0 until n) weights.add(reader.nextLong())
        for (i in 0 until n) need.add(true)

        for (i in 0 until m) {
            val capacity = reader.nextInt()
            list.add(TreeSet())
            for (j in 0 until capacity) {
                list[i].add(reader.nextInt())
            }
        }
        return Set(n, m, weights, need, list)
    }

    fun run() {
        reader = FastScanner(File("cycles" + ".in"))
        writer = FileWriter(File("cycles" + ".out"))

        solve()

        writer.close()
    }

    fun measureTime(name: String, f: () -> Unit) {
        val start = System.nanoTime()
        f()
        println("$name: run for ${(System.nanoTime() - start) / 10e9}")
    }


    class FastScanner(file: File) {
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

    data class Set(
        val n: Int,
        val m: Int,
        val weights: MutableList<Long>,
        val need: MutableList<Boolean>,
        val list: MutableList<TreeSet<Int>>
    )
}

fun main(args: Array<String>) {
    ProblemD().run()
}