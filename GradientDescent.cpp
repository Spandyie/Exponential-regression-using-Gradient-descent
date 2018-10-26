using namespace std;

class CSVReader {
private:

	string fileName;

public:
	CSVReader(string fileName) : fileName(fileName) 
	{ }

	vector<vector<double>> getData();

};

vector<vector<double>> CSVReader::getData() {

	ifstream file_object;
	file_object.open(fileName, ifstream::in);
	vector<vector<double>> data_double;
	string line = "";
	string delimiter = ",";
	while (getline(file_object, line)) {
		vector<string> line_of_file;
		// split the string
		boost::algorithm::split(line_of_file, line, boost::is_any_of(delimiter));
		vector<double> line_of_file_double;		
        // convert the string of double into double
		transform(line_of_file.begin(), line_of_file.end(), inserter(line_of_file_double, line_of_file_double.begin()), [](const string& s) { return stod(s);});
		data_double.push_back(line_of_file_double);					
	}
	return data_double;	
}


class Regression {
private:
	vector<double> m_x, m_y;
	pair<double, double> gradient(double& slope, double& intercept);
	static double loss(const vector<double>& y_hat, const vector<double>& y_true);

public:
	Regression(vector<double>& x, vector<double>& y) : m_x(x), m_y(y) {}
	pair<double, double> train(int n_iter, double lr);
	vector<double> predict(const double& s, const double& i, const vector<double>& inp_x);
};


pair<double, double> Regression::train(int n_iter, double lr) {
	/* Train the regression with gradient Descent*/
	mt19937 rng;
	rng.seed(random_device()());
	uniform_real_distribution<double> gen(0, 1);
	
	double slope_ = gen(rng);
	double intercept_ = -1.0 * gen(rng);

	double dslope_, dintercept_;
	pair<double, double> final_slope_intercept;
	for (int epoch = 0; epoch <= n_iter; epoch++) {
		pair<double, double> dslope_intercept = gradient(slope_, intercept_);
		// gradients of the slope and intercept
		dslope_ = dslope_intercept.first;
		dintercept_ = dslope_intercept.second;
		//cout << "Slope: " << dslope_ << " Intercept grad" << dintercept_ << "\n";
		// update the slope and intercept
		slope_ -= lr * dslope_;
		intercept_ -= lr * dintercept_;
		// display the slope and intercept
		if (epoch % 1000 == 0) {
			vector<double> y_hat = predict(slope_, intercept_, m_x);
			double loss_value = loss(y_hat, m_y);
			//cout << "Losss= " << loss_value << endl;
			//D(loss_value);
		}
	}
	// assign the value to slope and intercept
	final_slope_intercept.first = slope_;
	final_slope_intercept.second = intercept_;
	return final_slope_intercept;

}

vector<double> Regression::predict(const double& s, const double& i, const vector<double>& inp_x) {
	/* s: (double) slope
	i : (double) intercept
	inp_x: the vector<double> of input variable to be predicted
	*/
	vector<double> y(inp_x.size());
	for(size_t ind = 0; ind < y.size(); ind++){
		double temp = i + s * inp_x[ind];
		y[ind] = temp;
	}
	return y;
}

double Regression::loss(const vector<double>& y_hat, const vector<double>& y_true) {
	/* Estimate the mean-squared loss function
	y_hat : vector<double> of the predicted y
	y_true: vector<double> of the actual y-value
	*/
	vector<double> temp_diff;
	// take the difference of two vectors, add the difference to temp_diff vector
	transform(y_hat.begin(), y_hat.end(), y_true.begin(), inserter(temp_diff, temp_diff.begin()), minus<double>());
	double loss_value = inner_product(temp_diff.begin(), temp_diff.end(), temp_diff.begin(), 0);
	loss_value /= (double)temp_diff.size();
	return loss_value;
}

pair<double, double> Regression::gradient(double& s, double& i) {
	/* Estimates the grdients of slope and intercept parameters
	Argumets
	s : double slope parameters
	i : double intercept parameter
	Returns:
	pair<double, double>, returns a pair of gradients for slope and intercept
	*/
	auto m = m_x.size();
	vector<double> y_hat = predict(s, i, m_x);
	vector<double> err;
	transform(y_hat.begin(), y_hat.end(), m_y.begin(), inserter(err, err.begin()), minus<double>());
	// gradient of slope
	double dslope = (double) 1.0 / m * inner_product(err.begin(), err.end(), m_x.begin(), 0.0);
	//gradient of intercept
	double dintercept = (double) 1.0 / m * accumulate(err.begin(), err.end(), 0.0);
	pair<double, double> dslope_intercept(dslope, dintercept);
	return dslope_intercept;
}


void log_transform(vector<double>& y) {
	/* tranforms the y coordinated if the provided y vector*/
	transform(y.begin(), y.end(), y.begin(), [](const double& s){return log(s);});
}

int main()
{ 

	CSVReader reader("Input.csv");
	const auto output = reader.getData();
	
	vector<double> x;
	vector<double> y;
	for (const auto& val : output) {
		x.emplace_back(val[0]);
		y.emplace_back(val[1]);
	}
	cout <<"size of x"<< x.size() << "size of y"<< y.size()<<"\n";	
	log_transform(y);

	Regression regress(x, y);
	auto slope_intercept = regress.train(3.0e6, 1.0e-5);
	writeFile(slope_intercept);
  }
