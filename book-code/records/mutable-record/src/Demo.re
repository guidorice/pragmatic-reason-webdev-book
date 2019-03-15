type person = {
  name: string,
  mutable age: int
};


let happyBirthday = (someone:person) : unit => {
  someone.age = someone.age + 1;
  ()
};

let friend = {
  name: "Juanita Fulano",
  age: 34
};

happyBirthday(friend);
Js.log(friend.age); /* 35 */
