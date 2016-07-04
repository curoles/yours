name := "yours"

version := "0.0.1"

scalaVersion := "2.11.6"

scalacOptions in (Compile,doc) ++= Seq("-groups", "-implicits")
scalacOptions in (Compile,doc) ++= Seq("-diagrams")

libraryDependencies += "com.typesafe.akka" %% "akka-actor" % "2.4.7"

libraryDependencies += "org.scala-lang.modules" %% "scala-parser-combinators" % "1.0.2"

libraryDependencies += "org.scala-lang.modules" %% "scala-xml" % "1.0.2"
