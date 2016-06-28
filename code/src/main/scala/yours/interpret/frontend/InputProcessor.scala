/* Copyright Igor Lesik 2016
 *
 * Processes input text:
 *  - tokenizes text.
 */
package yours.interpret.frontend

import yours.grammar._

/** Processes user input text.
  *
  * 
  * [[file:htmlsrc/yours/InputProcessor.scala.html]]
  *
  * @author Igor Lesik 2016
  */
class InputProcessor {

  /** Tokenizes input text. */
  val sentenceParser = new SentenceParser

  /** To call like:
    * {{{
    * inputProcessor(text)
    * }}}
    */
  def apply(input: String) = process(input)

  /** Returns ?
    *
    */
  def process(input: String) = {
    val sentences = tokenize(input)
    if (sentences.successful) println("tokens:"+sentences.get)

    sentences.get.foreach {
      sentence => onNextSentence(sentence)
    }
  }

  /** Returns list of tokens as result
    * of parsing raw English text. 
    */
  def tokenize(text: String) = {
    val tokens = sentenceParser.parseAll(
      sentenceParser.text,
      text)

    //println("tokens:" + tokens)
    //if (result.successful) println(result.get)

    tokens
  }

  def onNextSentence(sentence:yours.grammar.SentenceToken) = {
    println("sentence:"+sentence)
    println("  words:"+sentence.words)
    sentence.words.foreach{word => println("    word:"+word)}
  }
}
