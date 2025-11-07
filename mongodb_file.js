const express = require('express');
const mongoose = require('mongoose');
const app = express();
app.use(express.urlencoded({ extended: true }));

// ✅ MongoDB Connection
mongoose.connect('mongodb://127.0.0.1:27017/ganeshdb')
  .then(() => console.log('✅ MongoDB Connected'))
  .catch(err => console.error(err));

// ✅ Schema & Model
const Student = mongoose.model('Student', new mongoose.Schema({
  name: String, age: Number, course: String
}));

// 🔹 Simple Layout
const layout = (title, body) => `
<html><head><title>${title}</title></head>
<body style="font-family:Arial;margin:40px;">
<h2>${title}</h2>${body}<br><a href="/">🏠 Home</a>
</body></html>`;

// 🏠 Home Page (Form)
app.get('/', (req, res) => res.send(layout('Student Form', `
<form action="/add" method="POST">
  <input name="name" placeholder="Name" required><br><br>
  <input name="age" type="number" placeholder="Age" required><br><br>
  <input name="course" placeholder="Course" required><br><br>
  <button type="submit">Add</button>
</form><br>
<a href="/students"><button>View All</button></a>
`)));

// ➕ Add Student
app.post('/add', async (req, res) => {
  await Student.create(req.body);
  console.log('✅ Added student:', req.body);
  res.redirect('/');
});

// 📖 View All + Update + Delete
app.get('/students', async (req, res) => {
  const all = await Student.find();
  console.log('📋 All Students:', all);

  if (all.length > 0) {
    // 🟢 Update 1st Student
    await Student.findByIdAndUpdate(all[0]._id, { name: 'jagadeesh', age: 99, course: 'ML' });
    console.log(`✏️ Updated 1st Student (${all[0]._id})`);
  }

  if (all.length > 1) {
    // 🔴 Delete 2nd Student
    await Student.findByIdAndDelete(all[1]._id);
    console.log(`❌ Deleted 2nd Student (${all[1]._id})`);
  }

  const updated = await Student.find();
  console.log('✅ Final Students List:', updated);

  

res.send(`
    <script>
      alert('✅ Check console for student records and operations performed.');
      window.location.href = '/';
    </script>
  `);
});

// 🚀 Start Server
app.listen(3000, () => console.log('🚀 Server running at http://localhost:3000'));
