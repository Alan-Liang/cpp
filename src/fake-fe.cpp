#include <iostream>
#include <string>

int main () {
  std::string name = "World";
  std::cout << R"(
HTTP/1.0 200 OK

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>)" + name + R"(;khjvbcx</title>
</head>
<body>
  <h1>Hello )" + name + R"(!</h1>
</body>
</html>
  )";
}
