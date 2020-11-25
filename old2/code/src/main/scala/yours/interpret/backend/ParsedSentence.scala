/* Copyright Igor Lesik 2016
 *
 * Parsed sentence.
 */
package yours.interpret.backend

class ParsedWord(
  val str:String,
  val token:yours.grammar.Token,
  val wordDef:Option[yours.word.WordDef]) {

}

class ParsedSentence {

  type Array[T] = collection.mutable.ArrayBuffer[T]

  val words: Array[ParsedWord] = new Array[ParsedWord]

  //TODO val terminal

  override def toString():String = {
    words.map(_.str).mkString(" ")
  }
}
