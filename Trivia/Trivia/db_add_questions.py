import requests
import json
import sqlite3
import time

def insert_to_questions_table(db_handler, question, incorrect_answers: list, correct_answer):
    if (len(incorrect_answers) == 3):
        db_handler.execute(f"INSERT INTO QUESTIONS VALUES('{question}','{incorrect_answers[0]}','{incorrect_answers[1]}','{incorrect_answers[2]}','{correct_answer}');")
    else:
        db_handler.execute(f"INSERT INTO QUESTIONS VALUES('{question}','{incorrect_answers[0]}','{incorrect_answers[0]}','{incorrect_answers[0]}','{correct_answer}');")

def main():
    json_api = requests.get("https://opentdb.com/api.php?amount=10")
    json_results_list = json.loads(json_api.text)["results"]
    db = sqlite3.connect("DB.sqlite")
    db_handler = db.cursor()

    for json_result in json_results_list:
        time.sleep(0.5)
        insert_to_questions_table(db, json_result["question"], json_result["incorrect_answers"], json_result["correct_answer"])

    db.commit()
    db.close()

if __name__ == '__main__':
    main()