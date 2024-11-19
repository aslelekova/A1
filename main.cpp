#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>

struct Circle {
  double x, y, r;
};

bool isInIntersection(double px, double py, const Circle& c1, const Circle& c2, const Circle& c3) {
  auto isInCircle = [](double px, double py, const Circle& c) {
    return (px - c.x) * (px - c.x) + (py - c.y) * (py - c.y) <= c.r * c.r;
  };
  return isInCircle(px, py, c1) && isInCircle(px, py, c2) && isInCircle(px, py, c3);
}

double exactArea() {
  double pi = M_PI;
  double theta = std::asin(0.8);
  return 0.25 * pi + 1.25 * theta - 1;
}

double monteCarloArea(const Circle& c1, const Circle& c2, const Circle& c3, int points, double& relativeError) {
  double minX = std::min({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
  double maxX = std::max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
  double minY = std::min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
  double maxY = std::max({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});
  double areaRect = (maxX - minX) * (maxY - minY);

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> disX(minX, maxX);
  std::uniform_real_distribution<> disY(minY, maxY);

  int insideCount = 0;
  for (int i = 0; i < points; ++i) {
    double px = disX(gen);
    double py = disY(gen);
    if (isInIntersection(px, py, c1, c2, c3)) {
      ++insideCount;
    }
  }

  double estimatedArea = areaRect * static_cast<double>(insideCount) / points;
  relativeError = std::abs(estimatedArea - exactArea()) / exactArea() * 100.0;
  return estimatedArea;
}

int main() {
  Circle c1 = {1.0, 1.0, 1.0};
  Circle c2 = {1.5, 2.0, std::sqrt(5.0) / 2.0};
  Circle c3 = {2.0, 1.5, std::sqrt(5.0) / 2.0};

  double exact = exactArea();
  std::cout << "Exact Area: " << std::fixed << std::setprecision(10) << exact << std::endl;

  std::ofstream results("monte_carlo_results.csv");
  results << "Points,EstimatedArea,RelativeError" << std::endl;

  for (int points = 100; points <= 100000; points += 500) {
    double relativeError;
    double estimated = monteCarloArea(c1, c2, c3, points, relativeError);
    std::cout << "Points: " << points << ", Estimated Area: " << estimated
              << ", Relative Error: " << relativeError << "%" << std::endl;
    results << points << "," << estimated << "," << relativeError << std::endl;
  }

  results.close();
  std::cout << "Results saved to monte_carlo_results.csv" << std::endl;

  return 0;
}
