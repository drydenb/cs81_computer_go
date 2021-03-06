// assume the command is in one of the forms above 
	try {
		// first form: 'id command_name arguments\n'
		iss >> token;    // assume this is the id 
		// try {
			
		// 	int id = stoi(token);    
		// 	gtp_cmd.id = id; 

		// 	iss >> token;    // this must now be the command 

		// }
		// catch (const invalid_argument &ia) {
		// 	// must be another form 
		// }
		// second form: 'id command_name\n'
		
		// third form: 'command_name arguments\n'
		
		// fourth form: 'command_name\n'
	}
	// otherwise, something went wrong while parsing 
	catch (...) {
		cerr << "Unable to parse command: \'";
		cerr << input << "\'" << endl; 
	}

	// istringstream iss(input);
	// string token;
	// iss >> token; 

	// // while we can get valid tokens, see if we can parse the command
	// bool found_id = false;
	// bool found_command = false;
	// bool valid_args = false; 

	// while (iss >> token) {
	// 	// cout << "Token is: \'" << token << "\'" << endl; 
	// 	// first token is either an id or a command_name
	// 	try {
	// 		int id = stoi(token);
	// 		found_id = true; 
	// 	} 
	// 	catch (const std::invalid_argument& ia) {
	// 		;
	// 	}
	// }	 









	// attempt to parse 
	// iss >> token;
	// try {
	// 	// assume we get an id 
	// 	cout << "In try..." << endl; 
	// 	cout << token << endl; 
	// 	int id = stoi(token);
	// 	gtp_cmd.has_id = true;
	// 	gtp_cmd.id = id; 

	// 	cout << id << endl; 
	// 	// so far so good 
	// 	iss >> token;
	// 	string command_name = token; 
	// 	gtp_cmd.command_name = command_name; 
	// 	cout << gtp_cmd.command_name << endl; 
	// }
	// catch (const invalid_argument &ia) {
	// 	// we didn't get a valid id. assume we get a command_name 
	// 	cout << "In catch..." << endl; 
	// 	string command_name = token; 
	// 	gtp_cmd.command_name = command_name; 
	// 	cout << gtp_cmd.command_name << endl; 	
	// }

	// // if the command is supported, parse its arguments 
	// unordered_map<string, int>::const_iterator cmd =
	// 				supported_commands.find(gtp_cmd.command_name);

	// if ( cmd == supported_commands.end() ) {
	// 	// didn't find the command_name
	// 	cerr << "Command not supported: \'" << gtp_cmd.command_name << "\'";
	// 	cerr << endl; 
	// 	return; 
	// } else {
	// 	// look up the number of arguments in the unordered map
	// 	int num_args = cmd->second;
	// 	cout << num_args << endl;  
	// }


	// this code implements GTP Protocol Version 2 
void gtp_protocol_version(GTP_Command &cmd) {
	// this command never fails  
	cmd.success_response = string("2");

	if (cmd.has_id) {
		string id = to_string(cmd.id);
		cmd.response = string("=" + id + " 2\n\n");
	} else {
		cmd.response = string("= 2\n\n"); 
	}
	return; 
}

// prints out the name of this engine. this doesn't matter -- just pick "Izumi"
void gtp_name(GTP_Command &cmd) {
	if (cmd.has_id) {
		string id = to_string(cmd.id);
		cmd.response = string("=" + id + " Izumi\n\n");
	} else {
		cmd.response = string("= Izumi\n\n"); 
	}
	return; 
}

// prints out the version number for this engine. since no sense of version return
// the empty string (compliant with GTP) 
void gtp_version(GTP_Command &cmd) {
	if (cmd.has_id) {
		string id = to_string(cmd.id);
		cmd.response = string("=" + id + "\n\n");
	} else {
		cmd.response = string("=\n\n");
	}
	return; 
}

// void gtp_known_command(GTP_Command &cmd) {
// 	if(cmd.has_id) {
// 		string id = to_string;
// 	}
// }



// void print_ascii(string s) {
// 	for (string::iterator it = s.begin(); it != s.end(); ++it) { 
// 		int ascii_code = static_cast<int>(*it);    // get the ascii code
// 		cout << "Original string:" << s;
// 		cout << "ASCII, space delim:" << ascii_code << " "; 
// 	}
// }

// we need to keep track of all valid commands so we know when we're given 
// invalid inputs 
// vector<string> valid_commands 
// {
// 	"protocol_version",
// 	"name",
// 	"known_command",
// 	"list_commands",
// 	"quit",
// 	"boardsize",
// 	"clear_board",
// 	"komi",
// 	"play",
// 	"genmove",
// };

/// 
/// \brief Parses a move from the GTP controller and returns a tuple that 
///        indexes into the internal representation of the board.  
/// It is the caller's job to ensure that param 'move' is cast to lowercase. 
/// param 'flag' is assumed to be passed in as false. 
/// 
tuple<int, int> parse_move(string move, bool &flag) {

	// parse the move into its component coordinates


	int y_coord;   
	char letter = move[0]; 

	// search for the letter of the move (the y-coordinate) in our 
	// alphabet_to_index map 
	unordered_map<char,int>::const_iterator it = 
		alphabet_to_index.find(letter);

	// if we didn't find the letter, then there is an error in parsing 
	if ( it == alphabet_to_index.end() ) {
		flag = true;    // toggle the error flag 
		tuple<int, int> dummy (0, 0);  
		return dummy; 
	} else {
		// retrieve the index 
		y_coord = it->second; 
	}

	// get the y_coordinate of the move 
	int x_coord = stoi(move.substr(1)); 
	--x_coord;

	// this x_coordinate isn't quite right yet, (i.e., A1 is the lower 
	// left hand corner). change the x_coordinate so it indexes from 
	// bottom to top instead of top to bottom. 
	// x_coord = (board.size - x_coord) + 1;

	// sanity check: 19 - 1 + 1 = 19, and 19 - 19 + 1 = 1.
	tuple<int, int> pair (x_coord, y_coord); 
	return pair; 
}