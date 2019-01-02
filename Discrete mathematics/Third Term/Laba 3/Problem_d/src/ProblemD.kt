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


    fun checkFirst(list: MutableList<Int>): Boolean {
        return list.contains(0)
    }

    fun checkSecond(list: MutableList<Int>): Boolean {
        for (set in list) {
            for (curSet in 0 until set) {
                if ((curSet and set) != curSet) {
                    continue
                }
                if ((curSet and set) !in list) {
                    return false
                }
            }
        }
        return true
    }

    fun checkThird(set: Set): Boolean {
        val (n, _, list, numberList) = set
        for (i in list.indices) {               // A
            for (j in list.indices) {           // B
                if (i == j)
                    continue
                if (numberList[i].size <= numberList[j].size)
                    continue
                val subtract = list[i] and (list[j].inv())
                var exists = false
                for (k in 0..Math.pow(2.0, n.toDouble()).toInt()) {
                    if ((subtract shr k) and 1 == 1) {
                        if (list[j] or (1 shl k) in list) {
                            exists = true
                            break
                        }
                    }
                }
                if (!exists)
                    return false

            }
        }

        return true
    }

    fun solve() {
        val set = read()
        val (_, _, list, _) = set

        if (checkFirst(list) && checkSecond(list) && checkThird(set))
            writer.write("YES")
        else
            writer.write("NO")
    }


    fun read(): Set {
        val n = reader.nextInt()
        val m = reader.nextInt()
        val list = mutableListOf<Int>()
        val numberList = mutableListOf<HashSet<Int>>()

        for (i in 0 until m) {
            val tmp = hashSetOf<Int>()
            val amount = reader.nextLong()
            var index = 0
            for (j in 0 until amount) {
                val number = reader.nextInt()
                index = index or (1 shl (number - 1))
                tmp.add(number)
            }
            numberList.add(tmp)
            list.add(index)
        }
        return Set(n, m, list, numberList)
    }

    fun run() {
        reader = FastScanner(File("check" + ".in"))
        writer = FileWriter(File("check" + ".out"))

        solve()

        writer.close()
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

    data class Set(val n: Int, val m: Int, val intList: MutableList<Int>, val numberList: MutableList<HashSet<Int>>)
}

fun main(args: Array<String>) {
    ProblemD().run()
}