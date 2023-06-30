#include <iostream>
#include <fstream>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

#include "gdal.h"
#include "ogrsf_frmts.h"

using namespace std;

namespace bg = boost::geometry;

typedef bg::model::point<double, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;

bg::index::rtree<pair<box, int>, bg::index::quadratic<8, 4>> rtree;

/// <summary>
/// Adds the recrangle from dataset to the rtree
/// </summary>
/// <param name="polygonEnvelope">MBR</param>
/// <param name="osm_id">OSM_ID</param>
void addRectangle(OGREnvelope* polygonEnvelope, int osm_id)
{
	point x(polygonEnvelope->MinX, polygonEnvelope->MinY);
	point y(polygonEnvelope->MaxX, polygonEnvelope->MaxY);

	box rectangle(x, y);

	rtree.insert(make_pair(rectangle, osm_id));
}

/// <summary>
/// Reads rectangle from input file
/// </summary>
/// <param name="test_path">path to inout file</param>
/// <returns>if file was successfully opened and rectangle</returns>
pair<bool, box> getPointsFromFile(string test_path)
{
	ifstream in(test_path);

	double x_min;
	double y_min;
	double x_max;
	double y_max;

	if (in.is_open())
	{
		in >> x_min >> y_min >> x_max >> y_max;
		return make_pair(true, box(point(x_min, y_min), point(x_max, y_max)));
		in.close();
	}

	return make_pair(false, box());
}

/// <summary>
/// Finds intersecting rectangles
/// </summary>
/// <param name="input_rectangle">rectangle from input file</param>
/// <param name="dataset">dataset</param>
/// <returns>pairs of rectangles and their osm_id</returns>
vector<pair<box, int>> findIntersectingRectangles(box input_rectangle, GDALDataset* dataset)
{
	auto&& layer = dataset->GetLayer(0);

	for (auto&& feature : layer)
	{
		const shared_ptr<OGREnvelope> polygonEnvelope(new OGREnvelope);
		auto* geometry = feature->GetGeometryRef();
		geometry->getEnvelope(polygonEnvelope.get());
		addRectangle(polygonEnvelope.get(), feature->GetFieldAsInteger(0));
	}

	vector<pair<box, int>> result;
	rtree.query(bg::index::intersects(input_rectangle), back_inserter(result));

	return result;
}

/// <summary>
/// Writes result to the output file
/// </summary>
/// <param name="output_path">path to the output file</param>
/// <param name="result">intersecting regtangles</param>
void printResult(string output_path, vector<pair<box, int>> result)
{
	ofstream out(output_path, ios::out);
	vector<int> osm_ids;

	for (int i = 0; i < result.size(); i++)
		osm_ids.push_back(result[i].second);

	sort(osm_ids.begin(), osm_ids.end());

	if (out.is_open())
	{
		for (int i = 0; i < result.size(); i++)
			out << osm_ids[i] << endl;
	}
}

int main(int argc, char** argv)
{
	if (argc < 4)
	{
		cout << "Wrong number of args";
		return -1;
	}

	pair<bool, box> input = getPointsFromFile(argv[2]);

	if (!input.first)
	{
		cout << "Cannot open test file.";
		return -1;
	}

	GDALAllRegister();

	stringstream ss;
	ss << argv[1] << "\\building-polygon.shp";
	string path = ss.str();

	GDALDataset* dataset = static_cast<GDALDataset*>(GDALOpenEx(
		path.c_str(),
		GDAL_OF_VECTOR,
		nullptr, nullptr, nullptr));

	if (dataset == nullptr)
	{
		cout << "Cannot open dataset." << endl;
		return -1;
	}

	vector<pair<box, int>> result = findIntersectingRectangles(input.second, dataset);
	printResult(argv[3], result);
}