name := "yours"

version := "0.0.1"

scalacOptions in (Compile,doc) ++= Seq("-groups", "-implicits")
scalacOptions in (Compile,doc) ++= Seq("-diagrams")
