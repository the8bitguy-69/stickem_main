#include <vector>

#define FILTER_NUMBER 5

extern volatile int touch1detected;
extern volatile int touch2detected;

extern volatile bool OLED_ConnectFlag;
extern volatile bool BH1750_ConnectFlag;
extern volatile bool SR04_ConnectFlag;
extern volatile bool AHT10_ConnectFlag;
extern volatile bool MPU6050_ConnectFlag;

extern unsigned long sr04_distance;

const int COMMAND_SIZE = 4;
const int NUM_MOTORS = 8;

int readingsCount = 0;
unsigned long filterArray[FILTER_NUMBER] = {0};
long ultrasonicMedian = -1;

////////////////////////////////////////////////
//  ____  ____  ____  _  _   ___  ____  ____  //
// / ___)(_  _)(  _ \/ )( \ / __)(_  _)/ ___) //
// \___ \  )(   )   /) \/ (( (__   )(  \___ \ //
// (____/ (__) (__\_)\____/ \___) (__) (____/ //
////////////////////////////////////////////////

struct CodeBlock {
  virtual void execute() = 0;
  std::vector<CodeBlock*> parse_code(std::string code);
};

struct START : public CodeBlock {
  std::vector<CodeBlock*> code;

  START(std::string block);
  void execute();
};

struct MV : CodeBlock {
  int duration;
  int movement[NUM_MOTORS];

  MV(std::string block);
  void execute();
};

struct IF : CodeBlock {
  std::string condition;
  std::vector<CodeBlock*> code;

  IF(std::string block);
  void execute();
};

struct IE : CodeBlock {
  std::string condition;
  std::vector<CodeBlock*> if_code;
  std::vector<CodeBlock*> else_code;

  IE(std::string block);
  void execute();
};

struct WT : CodeBlock {
  int duration;

  WT(std::string block);
  void execute();
};

struct WF : CodeBlock {
  std::string condition;

  WF(std::string block);
  void execute();
};

struct LF : CodeBlock {
  std::vector<CodeBlock*> code;

  LF(std::string block);
  void execute();
};

struct LT : CodeBlock {
  int count;
  std::vector<CodeBlock*> code;

  LT(std::string block);
  void execute();
};

struct LW : CodeBlock {
  std::string condition;
  std::vector<CodeBlock*> code;

  LW(std::string block);
  void execute();
};

//////////////////////////////////////////////////////////////////
//   ___  __   __ _  ____  __  ____  __  __   __ _   __   __    //
//  / __)/  \ (  ( \(    \(  )(_  _)(  )/  \ (  ( \ / _\ (  )   //
// ( (__(  O )/    / ) D ( )(   )(   )((  O )/    //    \/ (_/\ //
//  \___)\__/ \_)__)(____/(__) (__) (__)\__/ \_)__)\_/\_/\____/ //
//////////////////////////////////////////////////////////////////

int get_t1() {
  // Touch0=touchRead(Touch1);
  if (touch1detected) {
    return 1;
  }
  return 0;
}

int get_t2() {
  // Touch1=touchRead(Touch1_Pin);
  if (touch2detected) {
    return 1;
  }
  return 0;
}

int get_usinch() {
  if (SR04_ConnectFlag==1) {
    double length_inch = (double) sr04_distance * 0.3837;
    return (unsigned long) length_inch;
  }
  return 0;
}

int get_uscm() {
  if (SR04_ConnectFlag==1) {
    return sr04_distance;
  }
  return 0;
}

int get_accelX() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_accelY() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_accelZ() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_gyroXdeg() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_gyroYdeg() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_gyroZdeg() {
  if (MPU6050_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_tempCelsius() {
  if (AHT10_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_humidity() {
  if (AHT10_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int get_light() {
  if (BH1750_ConnectFlag==1) {
    return 0;
  }
  return 0;
}

int apply_operator(int op, int value1, int value2) {
  switch (op) {
    case 1:
      Serial.print(value1);
      Serial.print(" == ");
      Serial.println(value2);
      return value1 == value2;
    case 2:
      return value1 != value2;
    case 3: 
      return value1 < value2;
    case 4: 
      return value1 <= value2;
    case 5:
      return value1 > value2;
    case 6:
      return value1 >= value2;
    case 7:
      return value1 && value2;
    case 8: 
      return value1 || value2;
  };
  return 0;
}

int *evaluate_condition(std::string condition, int index) {
  int value, end_index;
  char character = condition[index];
  if (character == '(') {
    int *temp = evaluate_condition(condition, index + 1);
    value = temp[0];
    end_index = temp[1];
    if (end_index + 1 >= condition.length()) {
        return temp;
    }
  } else {
    int i = 1;
    while (((index + i) < condition.length()) && (condition[index + i] != ')')) {
        i++;
    }
    std::string variable = condition.substr(index, i);
    int return_value;
    if (!variable.compare("true")) {
      return_value = 1;
    } else if (!variable.compare("false")) {
      return_value = 0;
    } else if (!variable.compare("t1")) {
      return_value = get_t1();
    } else if (!variable.compare("t2")) {
      return_value = get_t2();
    } else if (!variable.compare("usinch")) {
      return_value = get_usinch();
    } else if (!variable.compare("uscm")) {
      return_value = get_uscm();
    } else if (!variable.compare("accelX")) {
      return_value = get_accelX();
    } else if (!variable.compare("accelY")) {
      return_value = get_accelY();
    } else if (!variable.compare("accelZ")) {
      return_value = get_accelZ();
    } else if (!variable.compare("gyroXdeg")) {
      return_value = get_gyroXdeg();
    } else if (!variable.compare("gyroYdeg")) {
      return_value = get_gyroYdeg();
    } else if (!variable.compare("gyroZdeg")) {
      return_value = get_gyroZdeg();
    } else if (!variable.compare("tempCelsius")) {
      return_value = get_tempCelsius();
    } else if (!variable.compare("humidity")) {
      return_value = get_humidity();
    } else if (!variable.compare("light")) {
      return_value = get_light();
    } else if (isdigit(variable[0])) {
      return_value = atoi(variable.c_str());
    } 

    int *output = new int[2];
    output[0] = return_value;
    output[1] = index + i;
    return output;
  };

  int *output = new int[2];
  output[0] = value;
  output[1] = end_index + 1;
  
  int op = 0; 

  char *op_string = new char [3];
  op_string[0] = condition[end_index + 1];
  op_string[1] = condition[end_index + 2];
  op_string[2] = '\0';

  switch(op_string[0]) {
    case '(':
      return output;
      break;
    case '=':
      op = 1;
      break;
    case '!':
      op = 2;
      break;
    case '<':
      if (op_string[1] == '=') {
        op = 4;
      } else {
        op = 3;
      }
      break;
    case '>':
      if (op_string[1] == '=') {
        op = 6;
      } else {
        op = 5;
      }
      break;
    case '&':
      op = 7;
      break;
    case '|':
      op = 8;
      break;
  };

  int j = 1;
  while (((end_index + j) < condition.length()) && (condition[end_index + j] != '(')) {
    j++;
  }
  int *temp2 = evaluate_condition(condition, end_index + j + 1);
  int value2 = temp2[0];
  temp2[0] = apply_operator(op, value, value2);
  temp2[1]++;
  Serial.print("result of operation ");
  Serial.print(op_string);
  Serial.print(" on (");
  Serial.print(value);
  Serial.print(") and (");
  Serial.print(value2);
  Serial.print("): ");
  Serial.print(temp2[0]);
  Serial.println("");

  return temp2;
}

////////////////////////////////////////////////
//  ____   __   ____  ____  ____  ____  ____  //
// (  _ \ / _\ (  _ \/ ___)(  __)(  _ \/ ___) //
//  ) __//    \ )   /\___ \ ) _)  )   /\___ \ //
// (__)  \_/\_/(__\_)(____/(____)(__\_)(____/ //
////////////////////////////////////////////////

std::vector<CodeBlock*> CodeBlock::parse_code(std::string code) {
  std::vector<CodeBlock*> instructions;

  int level = 0;
  int block_start_index = 0;
  for (int i = 0; i < code.length(); i++) {
    if (code[i] == '{') {
        // if { is encountered
        level ++;
    } else if (code[i] == '}') {
        // if } is encountered
        level --;
    } else if ( code[i] == ',' && level == 0 ) {
      // signifies end of 0th level block
      // this cuts the initial code into separate 0th level blocks
      std::string block = code.substr(block_start_index, (i-block_start_index+1));

      // get instruction name
      char * temp_block = new char[block.length() + 1];
      strcpy(temp_block, block.c_str());
      char * instruction = strtok(temp_block, ":");

      // create codeblock node
      CodeBlock* node_ptr;
      std::string temp_instr(instruction);
      // Serial.print(instruction);

      if (!temp_instr.compare("mv")) {
        node_ptr = new MV(block);
      } else if (!temp_instr.compare("if")) {
        node_ptr = new IF(block);
      } else if (!temp_instr.compare("ie")) {
        node_ptr = new IE(block);
      } else if (!temp_instr.compare("wt")) {
        node_ptr = new WT(block);
      } else if (!temp_instr.compare("wf")) {
        node_ptr = new WF(block);
      } else if (!temp_instr.compare("lf")) {
        node_ptr = new LF(block);
      } else if (!temp_instr.compare("lt")) {
        node_ptr = new LT(block);
      } else if (!temp_instr.compare("lw")) {
        node_ptr = new LW(block);
      }
      
      instructions.push_back(node_ptr); // for now this serves to debug 

      block_start_index = i + 1;
    }
  }
  return instructions;
}

START::START (std::string block) {
  code = parse_code(block);
  Serial.println("START block created");
}

MV::MV (std::string block) {

  //  movementBlock =           "mv:m1:m2:m3:m4:m5:m6:m7:m8:duration,"

  char * temp_block = new char[block.length() + 1];
  strcpy(temp_block, block.c_str());
  char * char_movement = strtok(temp_block, ":");

  for (int i = 0; i < NUM_MOTORS; i++) {
    char_movement = strtok(NULL, ":");
    std::string temp_movement_str(char_movement);
    if (!temp_movement_str.compare("-")) {
      movement[i] = -1;
    } else {
      movement[i] = atoi(char_movement);
    }
  }

  char_movement = strtok(NULL, ":");

  std::string temp_char_str(char_movement);
  if (!temp_char_str.compare("-,")) {
    duration = -1;
  } else {
    duration = atoi(char_movement);
  }
  
  Serial.println("MOVE block created");
}

IF::IF (std::string block) {

  //  ifBlock =                 "if:{condition}:{ifBranchBlocks},"

  int condition_end_id = block.find("}:");
  condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
  std::string remaining_code = block.substr(condition_end_id + 3, block.length() - condition_end_id - 5);
  // string length is ((end - start) - 2) to get rid of last "},"
  code = parse_code(remaining_code);
}

IE::IE (std::string block) {

  //  ifElseBlock =             "ie:{condition}:{ifBranchBlocks}:{elseBranchBlocks},"

  int condition_end_id = block.find("}:");
  condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
  int level = 0;
  int else_block_start = condition_end_id + 2; // skip "}:"
  for ( ; else_block_start < block.length(); else_block_start++) {
    if (block[else_block_start] == '{') {
      level++;
    } else if (block[else_block_start] == '}') {
      level--;
    } else if (block[else_block_start] == ':' && level == 0) {
      break;
    }
  }
  std::string if_remaining_code = block.substr(condition_end_id + 3, else_block_start - condition_end_id - 4);
  // else_block_start - (start index) - 2 + 1 to get rid of ending "}:"
  if_code = parse_code(if_remaining_code);

  std::string else_remaining_code = block.substr(else_block_start + 2, block.length() - else_block_start - 4);
  // (else_block_start + 2) to pass ":{"
  // string length is (block.length() - else_block_start) - 2 to get rid of "},"
  else_code = parse_code(else_remaining_code);
}

WT::WT (std::string block) {
  
  //  waitBlock =               "wt:{duration},"

  std::string str_duration = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
  duration = atoi(str_duration.c_str());
}

WF::WF (std::string block) {

  //  waitForBlock =            "wf:{condition},"

  condition = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
}

LF::LF (std::string block) {

  //  loopForeverBlock =        "lf:{loopInnerBlocks},"

  std::string loop_code = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
  code = parse_code(loop_code);
}

LT::LT (std::string block) {

  //  loopXTimes =              "lt:{count}:{loopInnerBlocks},"

  int count_end_id = block.find("}:");
  std::string str_count = block.substr(COMMAND_SIZE, count_end_id - COMMAND_SIZE);
  count = atoi(str_count.c_str());
  std::string remaining_code = block.substr(count_end_id + 3, block.length() - 1);
  code = parse_code(remaining_code);
}

LW::LW (std::string block) {

  //  loopWhileBlock =          "lw:{condition}:{loopInnerBlocks},"

  int condition_end_id = block.find("}:");
  condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
  std::string remaining_code = block.substr(condition_end_id + 3, block.length() - condition_end_id - 5);
  // string length is ((end - start) - 2) to get rid of last "},"
  code = parse_code(remaining_code);
}

/////////////////////////////////////////////////////////
//  ____  _  _  ____  ___  _  _  ____  __  ____  ____  //
// (  __)( \/ )(  __)/ __)/ )( \(_  _)/  \(  _ \/ ___) //
//  ) _)  )  (  ) _)( (__ ) \/ (  )( (  O ))   /\___ \ //
// (____)(_/\_)(____)\___)\____/ (__) \__/(__\_)(____/ //
/////////////////////////////////////////////////////////

void START::execute() {
  for (auto piece : code) {
    piece->execute();
    Serial.println("");
  }
}

void MV::execute() {
  for (int i = 0; i < NUM_MOTORS; i++) {
    if (movement[i] >= 0) {
      controlServo(i, movement[i]);
      Serial.print("RUNNING SERVO ");
      Serial.print(i+1);
      Serial.print(" at velocity of ");
      Serial.print(movement[i]);
      Serial.println("");
    }
  }

  if (duration >= 0) {
    Serial.print("WAITING for ");
    Serial.print(duration);
    Serial.print(" ms\n");
    delay(duration); 

    for (int i = 0; i < NUM_MOTORS; i++) {
      if (movement[i]) {
        Serial.print("STOPPING SERVO ");
        Serial.print(i+1);
        Serial.println("");
        controlServo(i, 0);
      }
    }
  }
}

void IF::execute() {
  int *result = evaluate_condition(condition, 0);
  if (result[0]) {
    Serial.print("EXECUTING IF in IF: ");
    Serial.print(condition.c_str());
    Serial.println("");
    for (auto piece : code) {
      piece->execute();
    }
  }
}

void IE::execute() {
  int *result = evaluate_condition(condition, 0);
  if (result[0]) {
    Serial.print("ENTERING IF in IF ELSE ");
    Serial.println(condition.c_str());
    for (auto piece : if_code) {
      piece->execute();
    }
  } else {
    Serial.print("ENTERING ELSE in IF ELSE ");
    Serial.println(condition.c_str());
    for (auto piece : else_code) {
      piece->execute();
    }
  }
}

void WT::execute() {
  Serial.print("WAITING for ");
  Serial.print(duration);
  Serial.println(" ms");
  delay(duration);
}

void WF::execute() {
  int *result = evaluate_condition(condition, 0);
  while (!result[0]) {
    Serial.print("WAITING for: ");
    Serial.println(condition.c_str());
    delay(1000);
    result = evaluate_condition(condition, 0);
  }
  Serial.print("DONE waiting for: ");
  Serial.println(condition.c_str());
}

void LF::execute() {
  while (true) {
    Serial.println("LOOPING FOREVER");
    for (auto piece : code) {
      piece->execute();
    }
    delay(1);
  }
}

void LT::execute() {
  for (int i = 1; i <= count; i++) {
    Serial.print("LOOP: ");
    Serial.print(i);
    Serial.print("/");
    Serial.println(count);
    for (auto piece : code) {
      piece->execute();
    }
  }
}

void LW::execute() {
  int *result = evaluate_condition(condition, 0);
  while (result[0]) {
    Serial.print("LOOPING WHILE: ");
    Serial.println(condition.c_str());
    for (auto piece : code) {
      piece->execute();
    }
    result = evaluate_condition(condition, 0); // to poll for any changes
  }
}

void bubble(int end_index) {
  for (int i = 0; i < end_index - 1; i++) {
    if (filterArray[i] > filterArray[i+1]) {
      // bubble swap
      unsigned long temp = filterArray[i];
      filterArray[i] = filterArray[i+1];
      filterArray[i+1] = temp;
    }
  }
}

void sortArray() {
  for (int i = FILTER_NUMBER; i > 0; i--) {
    bubble(i);
  }
}

unsigned long getArrayMedian() {
  int median_id = FILTER_NUMBER/2;
  return filterArray[median_id];
}






















// #include <vector>

// #define FILTER_NUMBER 5

// extern volatile int touch1detected;
// extern volatile int touch2detected;

// extern volatile bool OLED_ConnectFlag;
// extern volatile bool BH1750_ConnectFlag;
// extern volatile bool SR04_ConnectFlag;
// extern volatile bool AHT10_ConnectFlag;
// extern volatile bool MPU6050_ConnectFlag;

// extern unsigned long sr04_distance;

// const int COMMAND_SIZE = 4;
// const int NUM_MOTORS = 8;

// int readingsCount = 0;
// unsigned long filterArray[FILTER_NUMBER] = {0};
// long ultrasonicMedian = -1;

// ////////////////////////////////////////////////
// //  ____  ____  ____  _  _   ___  ____  ____  //
// // / ___)(_  _)(  _ \/ )( \ / __)(_  _)/ ___) //
// // \___ \  )(   )   /) \/ (( (__   )(  \___ \ //
// // (____/ (__) (__\_)\____/ \___) (__) (____/ //
// ////////////////////////////////////////////////

// struct CodeBlock {
//   virtual void execute() = 0;
//   std::vector<CodeBlock*> parse_code(std::string code);
// };

// struct START : public CodeBlock {
//   std::vector<CodeBlock*> code;

//   START(std::string block);
//   void execute();
// };

// struct MV : CodeBlock {
//   int duration;
//   int movement[NUM_MOTORS];

//   MV(std::string block);
//   void execute();
// };

// struct IF : CodeBlock {
//   std::string condition;
//   std::vector<CodeBlock*> code;

//   IF(std::string block);
//   void execute();
// };

// struct IE : CodeBlock {
//   std::string condition;
//   std::vector<CodeBlock*> if_code;
//   std::vector<CodeBlock*> else_code;

//   IE(std::string block);
//   void execute();
// };

// struct WT : CodeBlock {
//   int duration;

//   WT(std::string block);
//   void execute();
// };

// struct WF : CodeBlock {
//   std::string condition;

//   WF(std::string block);
//   void execute();
// };

// struct LF : CodeBlock {
//   std::vector<CodeBlock*> code;

//   LF(std::string block);
//   void execute();
// };

// struct LT : CodeBlock {
//   int count;
//   std::vector<CodeBlock*> code;

//   LT(std::string block);
//   void execute();
// };

// struct LW : CodeBlock {
//   std::string condition;
//   std::vector<CodeBlock*> code;

//   LW(std::string block);
//   void execute();
// };

// //////////////////////////////////////////////////////////////////
// //   ___  __   __ _  ____  __  ____  __  __   __ _   __   __    //
// //  / __)/  \ (  ( \(    \(  )(_  _)(  )/  \ (  ( \ / _\ (  )   //
// // ( (__(  O )/    / ) D ( )(   )(   )((  O )/    //    \/ (_/\ //
// //  \___)\__/ \_)__)(____/(__) (__) (__)\__/ \_)__)\_/\_/\____/ //
// //////////////////////////////////////////////////////////////////

// int get_t1() {
//   // Touch0=touchRead(Touch1);
//   if (touch1detected) {
//     return 1;
//   }
//   return 0;
// }

// int get_t2() {
//   // Touch1=touchRead(Touch1_Pin);
//   if (touch2detected) {
//     return 1;
//   }
//   return 0;
// }

// int get_usinch() {
//   if (SR04_ConnectFlag==1) {
//     double length_inch = (double) sr04_distance * 0.3837;
//     return (unsigned long) length_inch;
//   }
//   return 0;
// }

// int get_uscm() {
//   if (SR04_ConnectFlag==1) {
//     return sr04_distance;
//   }
//   return 0;
// }

// int get_accelX() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_accelY() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_accelZ() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_gyroXdeg() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_gyroYdeg() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_gyroZdeg() {
//   if (MPU6050_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_tempCelsius() {
//   if (AHT10_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_humidity() {
//   if (AHT10_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int get_light() {
//   if (BH1750_ConnectFlag==1) {
//     return 0;
//   }
//   return 0;
// }

// int apply_operator(int op, int value1, int value2) {
//   switch (op) {
//     case 1:
//       Serial.print(value1);
//       Serial.print(" == ");
//       Serial.println(value2);
//       return value1 == value2;
//     case 2:
//       return value1 != value2;
//     case 3: 
//       return value1 < value2;
//     case 4: 
//       return value1 <= value2;
//     case 5:
//       return value1 > value2;
//     case 6:
//       return value1 >= value2;
//     case 7:
//       return value1 && value2;
//     case 8: 
//       return value1 || value2;
//   };
//   return 0;
// }

// int *evaluate_condition(std::string condition, int index) {
//   int value, end_index;
//   char character = condition[index];
//   if (character == '(') {
//     int *temp = evaluate_condition(condition, index + 1);
//     value = temp[0];
//     end_index = temp[1];
//     if (end_index + 1 >= condition.length()) {
//         return temp;
//     }
//   } else {
//     int i = 1;
//     while (((index + i) < condition.length()) && (condition[index + i] != ')')) {
//         i++;
//     }
//     std::string variable = condition.substr(index, i);
//     int return_value;
//     if (!variable.compare("true")) {
//       return_value = 1;
//     } else if (!variable.compare("false")) {
//       return_value = 0;
//     } else if (!variable.compare("t1")) {
//       return_value = get_t1();
//     } else if (!variable.compare("t2")) {
//       return_value = get_t2();
//     } else if (!variable.compare("usinch")) {
//       return_value = get_usinch();
//     } else if (!variable.compare("uscm")) {
//       return_value = get_uscm();
//     } else if (!variable.compare("accelX")) {
//       return_value = get_accelX();
//     } else if (!variable.compare("accelY")) {
//       return_value = get_accelY();
//     } else if (!variable.compare("accelZ")) {
//       return_value = get_accelZ();
//     } else if (!variable.compare("gyroXdeg")) {
//       return_value = get_gyroXdeg();
//     } else if (!variable.compare("gyroYdeg")) {
//       return_value = get_gyroYdeg();
//     } else if (!variable.compare("gyroZdeg")) {
//       return_value = get_gyroZdeg();
//     } else if (!variable.compare("tempCelsius")) {
//       return_value = get_tempCelsius();
//     } else if (!variable.compare("humidity")) {
//       return_value = get_humidity();
//     } else if (!variable.compare("light")) {
//       return_value = get_light();
//     } else if (isdigit(variable[0])) {
//       return_value = atoi(variable.c_str());
//     } 

//     int *output = new int[2];
//     output[0] = return_value;
//     output[1] = index + i;
//     return output;
//   };

//   int *output = new int[2];
//   output[0] = value;
//   output[1] = end_index + 1;
  
//   int op = 0; 

//   char *op_string = new char [3];
//   op_string[0] = condition[end_index + 1];
//   op_string[1] = condition[end_index + 2];
//   op_string[2] = '\0';

//   switch(op_string[0]) {
//     case '(':
//       return output;
//       break;
//     case '=':
//       op = 1;
//       break;
//     case '!':
//       op = 2;
//       break;
//     case '<':
//       if (op_string[1] == '=') {
//         op = 4;
//       } else {
//         op = 3;
//       }
//       break;
//     case '>':
//       if (op_string[1] == '=') {
//         op = 6;
//       } else {
//         op = 5;
//       }
//       break;
//     case '&':
//       op = 7;
//       break;
//     case '|':
//       op = 8;
//       break;
//   };

//   int j = 1;
//   while (((end_index + j) < condition.length()) && (condition[end_index + j] != '(')) {
//     j++;
//   }
//   int *temp2 = evaluate_condition(condition, end_index + j + 1);
//   int value2 = temp2[0];
//   temp2[0] = apply_operator(op, value, value2);
//   temp2[1]++;
//   Serial.print("result of operation ");
//   Serial.print(op_string);
//   Serial.print(" on (");
//   Serial.print(value);
//   Serial.print(") and (");
//   Serial.print(value2);
//   Serial.print("): ");
//   Serial.print(temp2[0]);
//   Serial.println("");

//   return temp2;
// }

// ////////////////////////////////////////////////
// //  ____   __   ____  ____  ____  ____  ____  //
// // (  _ \ / _\ (  _ \/ ___)(  __)(  _ \/ ___) //
// //  ) __//    \ )   /\___ \ ) _)  )   /\___ \ //
// // (__)  \_/\_/(__\_)(____/(____)(__\_)(____/ //
// ////////////////////////////////////////////////

// std::vector<CodeBlock*> CodeBlock::parse_code(std::string code) {
//   std::vector<CodeBlock*> instructions;

//   int level = 0;
//   int block_start_index = 0;
//   for (int i = 0; i < code.length(); i++) {
//     if (code[i] == '{') {
//         // if { is encountered
//         level ++;
//     } else if (code[i] == '}') {
//         // if } is encountered
//         level --;
//     } else if ( code[i] == ',' && level == 0 ) {
//       // signifies end of 0th level block
//       // this cuts the initial code into separate 0th level blocks
//       std::string block = code.substr(block_start_index, (i-block_start_index+1));

//       // get instruction name
//       char * temp_block = new char[block.length() + 1];
//       strcpy(temp_block, block.c_str());
//       char * instruction = strtok(temp_block, ":");

//       // create codeblock node
//       CodeBlock* node_ptr;
//       std::string temp_instr(instruction);
//       // Serial.print(instruction);

//       if (!temp_instr.compare("mv")) {
//         node_ptr = new MV(block);
//       } else if (!temp_instr.compare("if")) {
//         node_ptr = new IF(block);
//       } else if (!temp_instr.compare("ie")) {
//         node_ptr = new IE(block);
//       } else if (!temp_instr.compare("wt")) {
//         node_ptr = new WT(block);
//       } else if (!temp_instr.compare("wf")) {
//         node_ptr = new WF(block);
//       } else if (!temp_instr.compare("lf")) {
//         node_ptr = new LF(block);
//       } else if (!temp_instr.compare("lt")) {
//         node_ptr = new LT(block);
//       } else if (!temp_instr.compare("lw")) {
//         node_ptr = new LW(block);
//       }
      
//       instructions.push_back(node_ptr); // for now this serves to debug 

//       block_start_index = i + 1;
//     }
//   }
//   return instructions;
// }

// START::START (std::string block) {
//   code = parse_code(block);
//   Serial.println("START block created");
// }

// MV::MV (std::string block) {

//   //  movementBlock =           "mv:m1:m2:m3:m4:m5:m6:m7:m8:duration,"

//   char * temp_block = new char[block.length() + 1];
//   strcpy(temp_block, block.c_str());
//   char * char_movement = strtok(temp_block, ":");

//   for (int i = 0; i < NUM_MOTORS; i++) {
//     char_movement = strtok(NULL, ":");
//     movement[i] = atoi(char_movement);
//   }

//   char_movement = strtok(NULL, ":");

//   std::string temp_char_str(char_movement);
//   if (!temp_char_str.compare("-,")) {
//     duration = -1;
//   } else {
//     duration = atoi(char_movement);
//   }
  
//   Serial.println("MOVE block created");
// }

// IF::IF (std::string block) {

//   //  ifBlock =                 "if:{condition}:{ifBranchBlocks},"

//   int condition_end_id = block.find("}:");
//   condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
//   std::string remaining_code = block.substr(condition_end_id + 3, block.length() - condition_end_id - 5);
//   // string length is ((end - start) - 2) to get rid of last "},"
//   code = parse_code(remaining_code);
// }

// IE::IE (std::string block) {

//   //  ifElseBlock =             "ie:{condition}:{ifBranchBlocks}:{elseBranchBlocks},"

//   int condition_end_id = block.find("}:");
//   condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
//   int level = 0;
//   int else_block_start = condition_end_id + 2; // skip "}:"
//   for ( ; else_block_start < block.length(); else_block_start++) {
//     if (block[else_block_start] == '{') {
//       level++;
//     } else if (block[else_block_start] == '}') {
//       level--;
//     } else if (block[else_block_start] == ':' && level == 0) {
//       break;
//     }
//   }
//   std::string if_remaining_code = block.substr(condition_end_id + 3, else_block_start - condition_end_id - 4);
//   // else_block_start - (start index) - 2 + 1 to get rid of ending "}:"
//   if_code = parse_code(if_remaining_code);

//   std::string else_remaining_code = block.substr(else_block_start + 2, block.length() - else_block_start - 4);
//   // (else_block_start + 2) to pass ":{"
//   // string length is (block.length() - else_block_start) - 2 to get rid of "},"
//   else_code = parse_code(else_remaining_code);
// }

// WT::WT (std::string block) {
  
//   //  waitBlock =               "wt:{duration},"

//   std::string str_duration = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
//   duration = atoi(str_duration.c_str());
// }

// WF::WF (std::string block) {

//   //  waitForBlock =            "wf:{condition},"

//   condition = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
// }

// LF::LF (std::string block) {

//   //  loopForeverBlock =        "lf:{loopInnerBlocks},"

//   std::string loop_code = block.substr(COMMAND_SIZE, block.length() - COMMAND_SIZE - 2);
//   code = parse_code(loop_code);
// }

// LT::LT (std::string block) {

//   //  loopXTimes =              "lt:{count}:{loopInnerBlocks},"

//   int count_end_id = block.find("}:");
//   std::string str_count = block.substr(COMMAND_SIZE, count_end_id - COMMAND_SIZE);
//   count = atoi(str_count.c_str());
//   std::string remaining_code = block.substr(count_end_id + 3, block.length() - 1);
//   code = parse_code(remaining_code);
// }

// LW::LW (std::string block) {

//   //  loopWhileBlock =          "lw:{condition}:{loopInnerBlocks},"

//   int condition_end_id = block.find("}:");
//   condition = block.substr(COMMAND_SIZE, condition_end_id - COMMAND_SIZE);
//   std::string remaining_code = block.substr(condition_end_id + 3, block.length() - condition_end_id - 5);
//   // string length is ((end - start) - 2) to get rid of last "},"
//   code = parse_code(remaining_code);
// }

// /////////////////////////////////////////////////////////
// //  ____  _  _  ____  ___  _  _  ____  __  ____  ____  //
// // (  __)( \/ )(  __)/ __)/ )( \(_  _)/  \(  _ \/ ___) //
// //  ) _)  )  (  ) _)( (__ ) \/ (  )( (  O ))   /\___ \ //
// // (____)(_/\_)(____)\___)\____/ (__) \__/(__\_)(____/ //
// /////////////////////////////////////////////////////////

// void START::execute() {
//   for (auto piece : code) {
//     piece->execute();
//     Serial.println("");
//   }
// }

// void MV::execute() {
//   for (int i = 0; i < NUM_MOTORS; i++) {
//     controlServo(i, movement[i]);
//     Serial.print("RUNNING SERVO ");
//     Serial.print(i+1);
//     Serial.print(" at velocity of ");
//     Serial.print(movement[i]);
//     Serial.println("");
// }

// if (duration >= 0) {
//     Serial.print("WAITING for ");
//     Serial.print(duration);
//     Serial.print(" ms\n");
//     delay(duration); 

//     for (int i = 0; i < NUM_MOTORS; i++) {
//       if (movement[i]) {
//         Serial.print("STOPPING SERVO ");
//         Serial.print(i+1);
//         Serial.println("");
//         controlServo(i, 0);
//       }
//     }
//   }
// }

// void IF::execute() {
//   int *result = evaluate_condition(condition, 0);
//   if (result[0]) {
//     Serial.print("EXECUTING IF in IF: ");
//     Serial.print(condition.c_str());
//     Serial.println("");
//     for (auto piece : code) {
//       piece->execute();
//     }
//   }
// }

// void IE::execute() {
//   int *result = evaluate_condition(condition, 0);
//   if (result[0]) {
//     Serial.print("ENTERING IF in IF ELSE ");
//     Serial.println(condition.c_str());
//     for (auto piece : if_code) {
//       piece->execute();
//     }
//   } else {
//     Serial.print("ENTERING ELSE in IF ELSE ");
//     Serial.println(condition.c_str());
//     for (auto piece : else_code) {
//       piece->execute();
//     }
//   }
// }

// void WT::execute() {
//   Serial.print("WAITING for ");
//   Serial.print(duration);
//   Serial.println(" ms");
//   delay(duration);
// }

// void WF::execute() {
//   int *result = evaluate_condition(condition, 0);
//   while (!result[0]) {
//     Serial.print("WAITING for: ");
//     Serial.println(condition.c_str());
//     delay(1000);
//     result = evaluate_condition(condition, 0);
//   }
//   Serial.print("DONE waiting for: ");
//   Serial.println(condition.c_str());
// }

// void LF::execute() {
//   while (true) {
//     Serial.println("LOOPING FOREVER");
//     for (auto piece : code) {
//       piece->execute();
//     }
//     delay(1);
//   }
// }

// void LT::execute() {
//   for (int i = 1; i <= count; i++) {
//     Serial.print("LOOP: ");
//     Serial.print(i);
//     Serial.print("/");
//     Serial.println(count);
//     for (auto piece : code) {
//       piece->execute();
//     }
//   }
// }

// void LW::execute() {
//   int *result = evaluate_condition(condition, 0);
//   while (result[0]) {
//     Serial.print("LOOPING WHILE: ");
//     Serial.println(condition.c_str());
//     for (auto piece : code) {
//       piece->execute();
//     }
//     result = evaluate_condition(condition, 0); // to poll for any changes
//   }
// }

// void bubble(int end_index) {
//   for (int i = 0; i < end_index - 1; i++) {
//     if (filterArray[i] > filterArray[i+1]) {
//       // bubble swap
//       unsigned long temp = filterArray[i];
//       filterArray[i] = filterArray[i+1];
//       filterArray[i+1] = temp;
//     }
//   }
// }

// void sortArray() {
//   for (int i = FILTER_NUMBER; i > 0; i--) {
//     bubble(i);
//   }
// }

// unsigned long getArrayMedian() {
//   int median_id = FILTER_NUMBER/2;
//   return filterArray[median_id];
// }