import yours._

/** Yours command line app.
  *
  * [[file:htmlsrc/Yours.scala.html]]
  */
object Yours extends App {

  Console.println("Yours: " + (args mkString ", "))

  val inputProcessor = new InputProcessor

  inputProcessor("Hello Igor, number 1 super-hero.")

import yours.word._
val wdb:WordDB = new FileWordDB("./wdb/")
if (!wdb.open) {println("can't open wdb")}
val res=wdb.find("hello")
println(res.getOrElse("oops"))
}

