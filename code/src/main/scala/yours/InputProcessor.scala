package yours

import yours.grammar._

/** Processes user input text.
 *
 * @author Igor Lesik 2016
 */
class InputProcessor {

  /// Tokenizes input text.
  val sentenceParser = new SentenceParser

  /** To call like:
   *  {{{
   *  inputProcessor(text)
   *  }}}
   */
  def apply(input: String) = process(input)

  /** Returns ?
   *
   */
  def process(input: String) = {
    val tokens = tokenize(input)

    tokens
  }

  /** Returns list of tokens as result
   *  of parsing raw English text. 
   */
  def tokenize(text: String) = {
    val result = sentenceParser.parseAll(
      sentenceParser.sentence,
      text)

    println("result:" + result)
    //if (result.successful) println(result.get)

    result
  }
}
