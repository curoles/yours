/* Copyright Igor Lesik 2016
 *
 * Parts of text: word, number and punctuation marks.
 */
package yours.grammar

/** Common superclass for all elements of text */
sealed abstract class Token
case class TerminalToken    (str: String) extends Token
case class SingleWordToken  (str: String) extends Token
case class CompoundWordToken(str: String) extends Token
case class NumberToken      (str: String) extends Token
case class CommaToken       (str: String) extends Token

case class SentenceToken(words:List[Token], terminal:TerminalToken) extends Token

object tokenToString {

def apply(t:Token): String = t match {
  case TerminalToken(s) => s
  case SingleWordToken(s) => s
  case CompoundWordToken(s) => s
  case NumberToken(s) => s
  case CommaToken(s) => s
  case _ => "error"
}

}

