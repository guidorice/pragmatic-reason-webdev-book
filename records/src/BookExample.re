module Book = {
  module Author = {
    type t = {
      firstName: string,
      lastName: string,
    };
  };
  
  type t = {
    title: string,
    author: Author.t,
    isbn13: string
  };
};

let b: Book.t = {
  title: "Anathem",
  author: {
      firstName: "Neal",
      lastName: "Stephenson"
  },
  isbn13: "978-0-06-147409-5"
};

Js.log(b.author.lastName); /* Stephenson */
  
